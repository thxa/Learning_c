#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main() {
    const char msg[] = "Hello\n";
    size_t msg_len = sizeof(msg) - 1;

    unsigned char code[] = {
        0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x00,       // mov rax,1 (sys_write)
        0x48, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0x00,       // mov rdi,1 (stdout)
        0x48, 0xbe, 0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00, // mov rsi,addr
        0x48, 0xc7, 0xc2, msg_len, 0x00, 0x00, 0x00,    // mov rdx,len
        0x0f, 0x05,                                     // syscall
        0x48, 0xc7, 0xc0, 0x3c, 0x00, 0x00, 0x00,       // mov rax,60 (exit)
        0x48, 0x31, 0xff,                               // xor rdi,rdi
        0x0f, 0x05                                      // syscall
    };

    Elf64_Ehdr eh = {0};
    memcpy(eh.e_ident, ELFMAG, SELFMAG);
    eh.e_ident[EI_CLASS] = ELFCLASS64;
    eh.e_ident[EI_DATA] = ELFDATA2LSB;
    eh.e_ident[EI_VERSION] = EV_CURRENT;
    eh.e_ident[EI_OSABI] = ELFOSABI_SYSV;
    eh.e_type = ET_EXEC;
    eh.e_machine = EM_X86_64;
    eh.e_version = EV_CURRENT;
    eh.e_phoff = sizeof(Elf64_Ehdr);
    eh.e_ehsize = sizeof(Elf64_Ehdr);
    eh.e_phentsize = sizeof(Elf64_Phdr);
    eh.e_phnum = 1;
    eh.e_entry = 0x400000 + sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr);

    Elf64_Phdr ph = {0};
    ph.p_type = PT_LOAD;
    ph.p_flags = PF_R | PF_X | PF_W;
    ph.p_offset = 0;
    ph.p_vaddr = 0x400000;
    ph.p_paddr = 0x400000;
    ph.p_filesz = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + sizeof(code) + msg_len;
    ph.p_memsz = ph.p_filesz;
    ph.p_align = 0x1000;

    // Patch msg address
    uint64_t msg_addr = 0x400000 + sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + sizeof(code);
    memcpy(&code[16], &msg_addr, sizeof(msg_addr));

    // افتح الملف
    int fd = open("hello", O_CREAT | O_RDWR | O_TRUNC, 0755);
    if (fd < 0) { perror("open"); exit(1); }

    size_t total_size = ph.p_filesz;

    // كبر حجم الملف
    if (ftruncate(fd, total_size) < 0) {
        perror("ftruncate");
        close(fd);
        exit(1);
    }

    // اعمل mmap
    void *map = mmap(NULL, total_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(1);
    }

    // انسخ المحتويات
    unsigned char *p = (unsigned char*)map;
    memcpy(p, &eh, sizeof(eh));
    memcpy(p + sizeof(eh), &ph, sizeof(ph));
    memcpy(p + sizeof(eh) + sizeof(ph), code, sizeof(code));
    memcpy(p + sizeof(eh) + sizeof(ph) + sizeof(code), msg, msg_len);

    // تأكد من كتابة التغييرات
    if (msync(map, total_size, MS_SYNC) < 0) {
        perror("msync");
    }

    munmap(map, total_size);
    close(fd);

    printf("ELF file 'hello' created with mmap. Run with ./hello\n");
    return 0;
}
