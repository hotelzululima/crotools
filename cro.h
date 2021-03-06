#ifndef CRO_H
#define CRO_H

#include <stdint.h>

enum CRO_Segment_Type
{
   SEG_TEXT = 0,
   SEG_RODATA = 1,
   SEG_DATA = 2,
   SEG_BSS = 3,
};

typedef struct
{
   uint32_t offset;
   uint32_t size;
   uint32_t type;
} CRO_Segment;

typedef struct
{
   uint32_t offs_name;
   uint32_t seg_offset;
} CRO_Symbol;

typedef struct
{
   uint32_t seg_offset;
   uint8_t type;
   uint8_t last_entry;
   uint8_t all_loaded;
   uint8_t reserved;
   uint32_t addend;
} CRO_Relocation;

typedef struct
{
   uint8_t hash_table[0x80];
   uint32_t magic;
   uint32_t offs_mod_name;
   uint32_t offs_next;
   uint32_t offs_prev;
   uint32_t size_file;
   uint32_t size_bss;
   uint32_t reserved_0;
   uint32_t reserved_1;
   uint32_t offs_control;
   uint32_t offs_prologue;
   uint32_t offs_epilogue;
   uint32_t offs_unresolved;
   uint32_t offs_text;
   uint32_t size_text;
   uint32_t offs_data;
   uint32_t size_data;
   uint32_t offs_name;
   uint32_t size_name;
   uint32_t offs_segments;
   uint32_t num_segments;
   
   // Exports
   uint32_t offs_symbol_exports;
   uint32_t num_symbol_exports;
   uint32_t offs_index_exports;
   uint32_t num_index_exports;
   uint32_t offs_export_symtab;
   uint32_t num_export_symtab;
   uint32_t offs_export_tree;
   uint32_t num_export_tree;
   
   // Imports
   uint32_t offs_import_module;
   uint32_t num_import_module;
   uint32_t offs_import_patches;
   uint32_t num_import_patches;
   uint32_t offs_symbol_imports;
   uint32_t num_symbol_imports;
   uint32_t offs_index_imports;
   uint32_t num_index_imports;
   uint32_t offs_offset_imports;
   uint32_t num_offset_imports;
   uint32_t offs_import_symtab;
   uint32_t num_import_symtab;
   
   // Weird static stuff
   uint32_t offs_offset_exports;
   uint32_t num_offset_exports;
   uint32_t offs_static_relocations;
   uint32_t num_static_relocations;
   
   CRO_Relocation* get_import_reloc(void* cro_data, int index)
   {
      return (CRO_Relocation*)((char*)cro_data + offs_import_patches + (index * sizeof(CRO_Relocation)));
   }
   
   CRO_Relocation* get_static_reloc(void* cro_data, int index)
   {
      return (CRO_Relocation*)((char*)cro_data + offs_static_relocations + (index * sizeof(CRO_Relocation)));
   }
   
   CRO_Symbol* get_export(void* cro_data, int index)
   {
      return (CRO_Symbol*)((char*)cro_data + offs_symbol_exports + (index * sizeof(CRO_Symbol)));
   }
   
   CRO_Symbol* get_import(void* cro_data, int index)
   {
      return (CRO_Symbol*)((char*)cro_data + offs_symbol_imports + (index * sizeof(CRO_Symbol)));
   }
   
   char* get_name(void* cro_data)
   {
      return (char*)cro_data + offs_mod_name;
   }
   
   void* get_text_data(void* cro_data)
   {
      return (void*)((char*)cro_data + offs_text);
   }
   
   void* get_data_data(void* cro_data)
   {
      return (void*)((char*)cro_data + offs_data);
   }
   
   CRO_Segment* get_segments(void* cro_data)
   {
      return (CRO_Segment*)((char*)cro_data + offs_segments);
   }
} CRO_Header;

#endif
