#include<stdio.h>
// #include <stdint.h>
#include<stdlib.h>
// #include<elf.h>
// #include<string.h>
// #include<time.h>

#define EI_NIDENT 16

/* Type for a 16-bit quantity.  */
typedef unsigned short Elf32_Half;
typedef unsigned short Elf64_Half;

/* Types for signed and unsigned 32-bit quantities.  */
typedef unsigned int Elf32_Word;
typedef	signed int  Elf32_Sword;
typedef unsigned int Elf64_Word;
typedef	signed int  Elf64_Sword;

/* Types for signed and unsigned 64-bit quantities.  */
typedef unsigned long int Elf32_Xword;
typedef	signed long int Elf32_Sxword;
typedef unsigned long int Elf64_Xword;
typedef	signed long int  Elf64_Sxword;

/* Type of addresses.  */
typedef unsigned int Elf32_Addr;
typedef unsigned long int Elf64_Addr;

/* Type of file offsets.  */
typedef unsigned int Elf32_Off;
typedef unsigned long int Elf64_Off;

/* Type for section indices, which are 16-bit quantities.  */
typedef unsigned short Elf32_Section;
typedef unsigned short Elf64_Section;

/* Type for version symbol information.  */
typedef Elf32_Half Elf32_Versym;
typedef Elf64_Half Elf64_Versym;


typedef struct {
        unsigned char   e_ident[EI_NIDENT];
        Elf32_Half      e_type;
        Elf32_Half      e_machine;
        Elf32_Word      e_version;
        Elf32_Addr      e_entry;
        Elf32_Off       e_phoff;
        Elf32_Off       e_shoff;
        Elf32_Word      e_flags;
        Elf32_Half      e_ehsize;
        Elf32_Half      e_phentsize;
        Elf32_Half      e_phnum;
        Elf32_Half      e_shentsize;
        Elf32_Half      e_shnum;
        Elf32_Half      e_shstrndx;
} Elf32_Ehdr;

typedef struct {
        unsigned char   e_ident[EI_NIDENT];
        Elf64_Half      e_type;
        Elf64_Half      e_machine;
        Elf64_Word      e_version;
        Elf64_Addr      e_entry;
        Elf64_Off       e_phoff;
        Elf64_Off       e_shoff;
        Elf64_Word      e_flags;
        Elf64_Half      e_ehsize;
        Elf64_Half      e_phentsize;
        Elf64_Half      e_phnum;
        Elf64_Half      e_shentsize;
        Elf64_Half      e_shnum;
        Elf64_Half      e_shstrndx;
} Elf64_Ehdr;


/* Section header.  */
typedef struct
{
  Elf32_Word	sh_name;		/* Section name (string tbl index) */
  Elf32_Word	sh_type;		/* Section type */
  Elf32_Word	sh_flags;		/* Section flags */
  Elf32_Addr	sh_addr;		/* Section virtual addr at execution */
  Elf32_Off	sh_offset;		/* Section file offset */
  Elf32_Word	sh_size;		/* Section size in bytes */
  Elf32_Word	sh_link;		/* Link to another section */

  Elf32_Word	sh_info;		/* Additional section information */
  Elf32_Word	sh_addralign;		/* Section alignment */
  Elf32_Word	sh_entsize;		/* Entry size if section holds table */
} Elf32_Shdr;

typedef struct
{
  Elf64_Word	sh_name;		/* Section name (string tbl index) */
  Elf64_Word	sh_type;		/* Section type */
  Elf64_Xword	sh_flags;		/* Section flags */
  Elf64_Addr	sh_addr;		/* Section virtual addr at execution */
  Elf64_Off	sh_offset;		/* Section file offset */
  Elf64_Xword	sh_size;		/* Section size in bytes */
  Elf64_Word	sh_link;		/* Link to another section */
  Elf64_Word	sh_info;		/* Additional section information */
  Elf64_Xword	sh_addralign;		/* Section alignment */
  Elf64_Xword	sh_entsize;		/* Entry size if section holds table */
} Elf64_Shdr;


/* Section compression header.  Used when SHF_COMPRESSED is set.  */

typedef struct
{
  Elf32_Word	ch_type;	/* Compression format.  */
  Elf32_Word	ch_size;	/* Uncompressed data size.  */
  Elf32_Word	ch_addralign;	/* Uncompressed data alignment.  */
} Elf32_Chdr;

typedef struct
{
  Elf64_Word	ch_type;	/* Compression format.  */
  Elf64_Word	ch_reserved;
  Elf64_Xword	ch_size;	/* Uncompressed data size.  */
  Elf64_Xword	ch_addralign;	/* Uncompressed data alignment.  */
} Elf64_Chdr;

/* Symbol table entry.  */

typedef struct
{
  Elf32_Word	st_name;		/* Symbol name (string tbl index) */
  Elf32_Addr	st_value;		/* Symbol value */
  Elf32_Word	st_size;		/* Symbol size */
  unsigned char	st_info;		/* Symbol type and binding */
  unsigned char	st_other;		/* Symbol visibility */
  Elf32_Section	st_shndx;		/* Section index */
} Elf32_Sym;

typedef struct
{
  Elf64_Word	st_name;		/* Symbol name (string tbl index) */
  unsigned char	st_info;		/* Symbol type and binding */
  unsigned char st_other;		/* Symbol visibility */
  Elf64_Section	st_shndx;		/* Section index */
  Elf64_Addr	st_value;		/* Symbol value */
  Elf64_Xword	st_size;		/* Symbol size */
} Elf64_Sym;

/* The syminfo section if available contains additional information about
   every dynamic symbol.  */

typedef struct
{
  Elf32_Half si_boundto;		/* Direct bindings, symbol bound to */
  Elf32_Half si_flags;			/* Per symbol flags */
} Elf32_Syminfo;

typedef struct
{
  Elf64_Half si_boundto;		/* Direct bindings, symbol bound to */
  Elf64_Half si_flags;			/* Per symbol flags */
} Elf64_Syminfo;


/* Relocation table entry without addend (in section of type SHT_REL).  */

typedef struct
{
  Elf32_Addr	r_offset;		/* Address */
  Elf32_Word	r_info;			/* Relocation type and symbol index */
} Elf32_Rel;

/* I have seen two different definitions of the Elf64_Rel and
   Elf64_Rela structures, so we'll leave them out until Novell (or
   whoever) gets their act together.  */
/* The following, at least, is used on Sparc v9, MIPS, and Alpha.  */

typedef struct
{
  Elf64_Addr	r_offset;		/* Address */
  Elf64_Xword	r_info;			/* Relocation type and symbol index */
} Elf64_Rel;

/* Relocation table entry with addend (in section of type SHT_RELA).  */

typedef struct
{
  Elf32_Addr	r_offset;		/* Address */
  Elf32_Word	r_info;			/* Relocation type and symbol index */
  Elf32_Sword	r_addend;		/* Addend */
} Elf32_Rela;

typedef struct
{
  Elf64_Addr	r_offset;		/* Address */
  Elf64_Xword	r_info;			/* Relocation type and symbol index */
  Elf64_Sxword	r_addend;		/* Addend */
} Elf64_Rela;

/* RELR relocation table entry */

typedef Elf32_Word	Elf32_Relr;
typedef Elf64_Xword	Elf64_Relr;

/* Program segment header.  */

typedef struct
{
  Elf32_Word	p_type;			/* Segment type */
  Elf32_Off	p_offset;		/* Segment file offset */
  Elf32_Addr	p_vaddr;		/* Segment virtual address */
  Elf32_Addr	p_paddr;		/* Segment physical address */
  Elf32_Word	p_filesz;		/* Segment size in file */
  Elf32_Word	p_memsz;		/* Segment size in memory */
  Elf32_Word	p_flags;		/* Segment flags */
  Elf32_Word	p_align;		/* Segment alignment */
} Elf32_Phdr;

typedef struct
{
  Elf64_Word	p_type;			/* Segment type */
  Elf64_Word	p_flags;		/* Segment flags */
  Elf64_Off	p_offset;		/* Segment file offset */
  Elf64_Addr	p_vaddr;		/* Segment virtual address */
  Elf64_Addr	p_paddr;		/* Segment physical address */
  Elf64_Xword	p_filesz;		/* Segment size in file */
  Elf64_Xword	p_memsz;		/* Segment size in memory */
  Elf64_Xword	p_align;		/* Segment alignment */
} Elf64_Phdr;

/* Dynamic section entry.  */

typedef struct
{
  Elf32_Sword	d_tag;			/* Dynamic entry type */
  union
    {
      Elf32_Word d_val;			/* Integer value */
      Elf32_Addr d_ptr;			/* Address value */
    } d_un;
} Elf32_Dyn;

typedef struct
{
  Elf64_Sxword	d_tag;			/* Dynamic entry type */
  union
    {
      Elf64_Xword d_val;		/* Integer value */
      Elf64_Addr d_ptr;			/* Address value */
    } d_un;
} Elf64_Dyn;

/* Version definition sections.  */

typedef struct
{
  Elf32_Half	vd_version;		/* Version revision */
  Elf32_Half	vd_flags;		/* Version information */
  Elf32_Half	vd_ndx;			/* Version Index */
  Elf32_Half	vd_cnt;			/* Number of associated aux entries */
  Elf32_Word	vd_hash;		/* Version name hash value */
  Elf32_Word	vd_aux;			/* Offset in bytes to verdaux array */
  Elf32_Word	vd_next;		/* Offset in bytes to next verdef
					   entry */
} Elf32_Verdef;

typedef struct
{
  Elf64_Half	vd_version;		/* Version revision */
  Elf64_Half	vd_flags;		/* Version information */
  Elf64_Half	vd_ndx;			/* Version Index */
  Elf64_Half	vd_cnt;			/* Number of associated aux entries */
  Elf64_Word	vd_hash;		/* Version name hash value */
  Elf64_Word	vd_aux;			/* Offset in bytes to verdaux array */
  Elf64_Word	vd_next;		/* Offset in bytes to next verdef
					   entry */
} Elf64_Verdef;


/* Auxiliary version information.  */

typedef struct
{
  Elf32_Word	vda_name;		/* Version or dependency names */
  Elf32_Word	vda_next;		/* Offset in bytes to next verdaux
					   entry */
} Elf32_Verdaux;

typedef struct
{
  Elf64_Word	vda_name;		/* Version or dependency names */
  Elf64_Word	vda_next;		/* Offset in bytes to next verdaux
					   entry */
} Elf64_Verdaux;


/* Version dependency section.  */

typedef struct
{
  Elf32_Half	vn_version;		/* Version of structure */
  Elf32_Half	vn_cnt;			/* Number of associated aux entries */
  Elf32_Word	vn_file;		/* Offset of filename for this
					   dependency */
  Elf32_Word	vn_aux;			/* Offset in bytes to vernaux array */
  Elf32_Word	vn_next;		/* Offset in bytes to next verneed
					   entry */
} Elf32_Verneed;

typedef struct
{
  Elf64_Half	vn_version;		/* Version of structure */
  Elf64_Half	vn_cnt;			/* Number of associated aux entries */
  Elf64_Word	vn_file;		/* Offset of filename for this
					   dependency */
  Elf64_Word	vn_aux;			/* Offset in bytes to vernaux array */
  Elf64_Word	vn_next;		/* Offset in bytes to next verneed
					   entry */
} Elf64_Verneed;

/* Auxiliary needed version information.  */

typedef struct
{
  Elf32_Word	vna_hash;		/* Hash value of dependency name */
  Elf32_Half	vna_flags;		/* Dependency specific information */
  Elf32_Half	vna_other;		/* Unused */
  Elf32_Word	vna_name;		/* Dependency name string offset */
  Elf32_Word	vna_next;		/* Offset in bytes to next vernaux
					   entry */
} Elf32_Vernaux;

typedef struct
{
  Elf64_Word	vna_hash;		/* Hash value of dependency name */
  Elf64_Half	vna_flags;		/* Dependency specific information */
  Elf64_Half	vna_other;		/* Unused */
  Elf64_Word	vna_name;		/* Dependency name string offset */
  Elf64_Word	vna_next;		/* Offset in bytes to next vernaux
					   entry */
} Elf64_Vernaux;

typedef struct
{
  unsigned int a_type;		/* Entry type */
  union
    {
      unsigned int a_val;		/* Integer value */
      /* We use to have pointer elements added here.  We cannot do that,
	 though, since it does not work when using 32-bit definitions
	 on 64-bit platforms and vice versa.  */
    } a_un;
} Elf32_auxv_t;

typedef struct
{
  unsigned long int a_type;		/* Entry type */
  union
    {
      unsigned long int a_val;		/* Integer value */
      /* We use to have pointer elements added here.  We cannot do that,
	 though, since it does not work when using 32-bit definitions
	 on 64-bit platforms and vice versa.  */
    } a_un;
} Elf64_auxv_t;


/* Note section contents.  Each entry in the note section begins with
   a header of a fixed form.  */

typedef struct
{
  Elf32_Word n_namesz;			/* Length of the note's name.  */
  Elf32_Word n_descsz;			/* Length of the note's descriptor.  */
  Elf32_Word n_type;			/* Type of the note.  */
} Elf32_Nhdr;

typedef struct
{
  Elf64_Word n_namesz;			/* Length of the note's name.  */
  Elf64_Word n_descsz;			/* Length of the note's descriptor.  */
  Elf64_Word n_type;			/* Type of the note.  */
} Elf64_Nhdr;


/* Move records.  */
typedef struct
{
  Elf32_Xword m_value;		/* Symbol value.  */
  Elf32_Word m_info;		/* Size and index.  */
  Elf32_Word m_poffset;		/* Symbol offset.  */
  Elf32_Half m_repeat;		/* Repeat count.  */
  Elf32_Half m_stride;		/* Stride info.  */
} Elf32_Move;

typedef struct
{
  Elf64_Xword m_value;		/* Symbol value.  */
  Elf64_Xword m_info;		/* Size and index.  */
  Elf64_Xword m_poffset;	/* Symbol offset.  */
  Elf64_Half m_repeat;		/* Repeat count.  */
  Elf64_Half m_stride;		/* Stride info.  */
} Elf64_Move;


/* Entries found in sections of type SHT_MIPS_GPTAB.  */

typedef union
{
  struct
    {
      Elf32_Word gt_current_g_value;	/* -G value used for compilation.  */
      Elf32_Word gt_unused;		/* Not used.  */
    } gt_header;			/* First entry in section.  */
  struct
    {
      Elf32_Word gt_g_value;		/* If this value were used for -G.  */
      Elf32_Word gt_bytes;		/* This many bytes would be used.  */
    } gt_entry;				/* Subsequent entries in section.  */
} Elf32_gptab;

/* Entry found in sections of type SHT_MIPS_REGINFO.  */

typedef struct
{
  Elf32_Word ri_gprmask;		/* General registers used.  */
  Elf32_Word ri_cprmask[4];		/* Coprocessor registers used.  */
  Elf32_Sword ri_gp_value;		/* $gp register value.  */
} Elf32_RegInfo;

/* Entries found in sections of type SHT_MIPS_OPTIONS.  */

typedef struct
{
  unsigned char kind;		/* Determines interpretation of the
				   variable part of descriptor.  */
  unsigned char size;		/* Size of descriptor, including header.  */
  Elf32_Section section;	/* Section header index of section affected,
				   0 for global options.  */
  Elf32_Word info;		/* Kind-specific information.  */
} Elf_Options;

/* Entry found in `.options' section.  */

typedef struct
{
  Elf32_Word hwp_flags1;	/* Extra flags.  */
  Elf32_Word hwp_flags2;	/* Extra flags.  */
} Elf_Options_Hw;

/* Entries found in sections of type SHT_MIPS_LIBLIST.  */

typedef struct
{
  Elf32_Word l_name;		/* Name (string table index) */
  Elf32_Word l_time_stamp;	/* Timestamp */
  Elf32_Word l_checksum;	/* Checksum */
  Elf32_Word l_version;		/* Interface version */
  Elf32_Word l_flags;		/* Flags */
} Elf32_Lib;

typedef struct
{
  Elf64_Word l_name;		/* Name (string table index) */
  Elf64_Word l_time_stamp;	/* Timestamp */
  Elf64_Word l_checksum;	/* Checksum */
  Elf64_Word l_version;		/* Interface version */
  Elf64_Word l_flags;		/* Flags */
} Elf64_Lib;

/* Entries found in sections of type SHT_MIPS_CONFLICT.  */

typedef Elf32_Addr Elf32_Conflict;

typedef struct
{
  /* Version of flags structure.  */
  Elf32_Half version;
  /* The level of the ISA: 1-5, 32, 64.  */
  unsigned char isa_level;
  /* The revision of ISA: 0 for MIPS V and below, 1-n otherwise.  */
  unsigned char isa_rev;
  /* The size of general purpose registers.  */
  unsigned char gpr_size;
  /* The size of co-processor 1 registers.  */
  unsigned char cpr1_size;
  /* The size of co-processor 2 registers.  */
  unsigned char cpr2_size;
  /* The floating-point ABI.  */
  unsigned char fp_abi;
  /* Processor-specific extension.  */
  Elf32_Word isa_ext;
  /* Mask of ASEs used.  */
  Elf32_Word ases;
  /* Mask of general flags.  */
  Elf32_Word flags1;
  Elf32_Word flags2;
} Elf_MIPS_ABIFlags_v0;




int
main(int argc, char ** args)
{

    FILE *file;
    Elf64_Ehdr buffer;
    // Open the binary file for reading
    file = fopen("/bin/file", "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the integers from the file into the buffer
    fread(&buffer, sizeof(Elf64_Ehdr), 1, file);
    // printf("%x\n", buffer .e_ident);
    for(unsigned char *i= buffer.e_ident; i< buffer.e_ident + EI_NIDENT; i+= sizeof(unsigned char) ) {
        printf("%x", *i);
    }
    printf("\n");
    for(unsigned char *i= buffer.e_ident; i< buffer.e_ident + EI_NIDENT; i+= sizeof(unsigned char) ) {
        printf("%c", *i);
    }
    printf("\n");



    printf("\n");
    printf("%x\n", buffer .e_machine);
    printf("%x\n", buffer .e_type);
    printf("%x\n", buffer .e_version);
    printf("%x\n", buffer .e_ehsize);

    // Close the file
    fclose(file);
   return 0;
}
