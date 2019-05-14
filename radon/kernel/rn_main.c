#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <tty.h>
#include <multiboot.h>

#if defined(__linux__)
	#error Please use the appropriate cross compiler
#endif

#if !defined(__i386__)
	#error Please use the appropriate cross compiler
#endif

static void verify_grub2(unsigned long magic, unsigned long addr) {
    struct multiboot_tag *tag;
    const char *t = "true";
    const char *f = "false";
    const char *decision;
    unsigned size = 0;

    decision = MULTIBOOT2_BOOTLOADER_MAGIC == magic ? t : f;
    printk("[GRUB2] Magic number = 0x%x: %s\n", MULTIBOOT2_BOOTLOADER_MAGIC, decision);

    decision = addr & 0x7 ? f : t;
    printk("[GRUB2] Multiboot structure aligned: %s\n", decision);

    size = *((unsigned *) addr);
    printk("[GRUB2] Declared multiboot structure size: 0x%x\n", size);

    for(tag = (struct multiboot_tag *)(addr + 8); 
        MULTIBOOT_TAG_TYPE_END != tag->type; 
        tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag + ((tag->size + 7) & ~7))) {

        //printk("[GRUB2] Tag: 0x%x of size 0x%x\n", tag->type, tag->size);

        switch(tag->type) {
            case MULTIBOOT_TAG_TYPE_CMDLINE:
                printk("[GRUB2] Command line: %s\n",
                                ((struct multiboot_tag_string *)tag)->string);
                break;
            case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
                printk("[GRUB2] Bootloader name: %s\n", 
                                ((struct multiboot_tag_string *)tag)->string);
                break;
            case MULTIBOOT_TAG_TYPE_MODULE:
                printk("[GRUB2] Module at 0x%x - 0x%x. Command line: %s\n",
                                ((struct multiboot_tag_module *)tag)->mod_start,
                                ((struct multiboot_tag_module *)tag)->mod_end,
                                ((struct multiboot_tag_module *)tag)->cmdline);
                break;
            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
                printk("[GRUB2] Memory lower = %dKiB; Memory upper = %dKiB\n",
                                ((struct multiboot_tag_basic_meminfo *)tag)->mem_lower,
                                ((struct multiboot_tag_basic_meminfo *)tag)->mem_upper);
                break;
            case MULTIBOOT_TAG_TYPE_BOOTDEV:
                printk("[GRUB2] Boot device 0x%x, %u, %u\n",
                                ((struct multiboot_tag_bootdev *)tag)->biosdev,
                                ((struct multiboot_tag_bootdev *)tag)->slice,
                                ((struct multiboot_tag_bootdev *)tag)->part);
                break;
            case MULTIBOOT_TAG_TYPE_MMAP: {
                multiboot_memory_map_t *mmap;
                
                printk("[GRUB2] Memory mapping\n");

                for(mmap = ((struct multiboot_tag_mmap *)tag)->entries;
                    (multiboot_uint8_t *)mmap < (multiboot_uint8_t *)tag + tag->size;
                    mmap = (multiboot_memory_map_t *)((unsigned long)mmap + 
                            ((struct multiboot_tag_mmap *)tag)->entry_size)) {
                    printk("\tBase address = 0x%x%x,"
                           " Length = 0x%x%x,"
                           " Type = 0x%x\n",
                           (unsigned)(mmap->addr >> 32),
                           (unsigned)(mmap->addr & 0xFFFFFFFF),
                           (unsigned)(mmap->len >> 32),
                           (unsigned)(mmap->len & 0xFFFFFFFF),
                           (unsigned)mmap->type);
                }
            }

                break;
            case MULTIBOOT_TAG_TYPE_VBE:
                printk("[GRUB2] Multiboot tag type vbe\n");
                break;
/*            case MULTIBOOT_TAG_TYPE_FRAMEBUFFER: {
                multiboot_uint32_t color;
                unsigned i;
                struct multiboot_tag_framebuffer *fb_tag = (struct multiboot_tag_framebuffer *)tag;
                void *fb = (void *)(unsigned long)fb_tag->common.framebuffer_addr;

                switch(fb_tag->common.framebuffer_type) {
                    case MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED: {
                        unsigned best_distance;
                        unsigned distance;
                        struct multiboot_color *palette;

                        palette = fb_tag->framebuffer_palette;

                        color = 0;
                        best_distance = 4 * 256 * 256;

                        for(i = 0; i < fb_tag->framebuffer_palette_num_colors; i++) {
                            distance = (0xFF - palette[i].blue) * (0xFF - palette[i].blue)
                                       + palette[i].red * palette[i].red
                                       + palette[i].green * palette[i].green;

                            if(distance < best_distance) {
                                color = i;
                                best_distance = distance;
                            }   
                        }
                    }

                        break;

                    case MULTIBOOT_FRAMEBUFFER_TYPE_RGB:
                        color = ((1 << fb_tag->framebuffer_blue_mask_size) - 1) 
                                << fb_tag->framebuffer_blue_field_position; 
                        break;

                    case MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT:
                        color = '\\' | 0x0100;
                        break;

                    default:
                        color = 0xFFFFFFFF;
                        break;
                }

                for(i = 0; i < fb_tag->common.framebuffer_width 
                                && i < fb_tag->common.framebuffer_height; i++) {
                    switch(fb_tag->common.framebuffer_bpp) {
                        case 8: {
                            multiboot_uint8_t *pixel = fb + fb_tag->common.framebuffer_pitch * i + i;
                            *pixel = color;
                        }

                            break;

                        case 15:
                            // Fallthrough
                        case 16: {
                            multiboot_uint16_t *pixel = fb 
                                                        + fb_tag->common.framebuffer_pitch 
                                                        * i + 2 * i;
                            *pixel = color;
                        }

                            break;

                        case 24: {
                            multiboot_uint32_t *pixel = fb
                                                        + fb_tag->common.framebuffer_pitch
                                                        * i + 3 * i;
                            *pixel = (color & 0xFFFFFF) | (*pixel & 0xFF000000);
                        }

                            break;

                        case 32: {
                            multiboot_uint32_t *pixel = fb
                                                        + fb_tag->common.framebuffer_pitch
                                                        * i + 4 * i;
                            *pixel = color;
                        }

                            break;
                    }
                }

                break;
*/              
            case MULTIBOOT_TAG_TYPE_ELF_SECTIONS:
                printk("[GRUB2] Multiboot tag type elf sections\n");
                break;
            case MULTIBOOT_TAG_TYPE_APM:
                printk("[GRUB2] Multiboot tag type APM\n");
                break;
            case MULTIBOOT_TAG_TYPE_EFI32:
                printk("[GRUB2] Multiboot tag type EFI32\n");
                break;
            case MULTIBOOT_TAG_TYPE_EFI64:
                printk("[GRUB2] Multiboot tag type EFI64\n");
                break;
            case MULTIBOOT_TAG_TYPE_SMBIOS:
                printk("[GRUB2] Multiboot tag type SMBIOS\n");
                break;
            case MULTIBOOT_TAG_TYPE_ACPI_OLD:
                printk("[GRUB2] Multiboot tag type ACPI old\n");
                break;
            case MULTIBOOT_TAG_TYPE_ACPI_NEW:
                printk("[GRUB2] Multiboot tag type ACPI new\n");
                break;
            case MULTIBOOT_TAG_TYPE_NETWORK:
                printk("[GRUB2] Multiboot tag type network\n");
                break;
            case MULTIBOOT_TAG_TYPE_EFI_MMAP:
                printk("[GRUB2] Multiboot tag type EFI mmap\n");
                break;
            case MULTIBOOT_TAG_TYPE_EFI_BS:
                printk("[GRUB2] Multiboot tag type EFI BS\n");
                break;
            case MULTIBOOT_TAG_TYPE_EFI32_IH:
                printk("[GRUB2] Multiboot tag type EFI32 IH\n");
                break;
            case MULTIBOOT_TAG_TYPE_EFI64_IH:
                printk("[GRUB2] Multiboot tag type EFI64 IH\n");
                break;
            case MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR:
                printk("[GRUB2] Multiboot tag type load base addr\n");
                break;
            default:
                printk("[GRUB2] Unkown tag type\n");
                break;
        } 
    }

    tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag + ((tag->size + 7) & ~7));
    printk("[GRUB2] Total multiboot struct size: 0x%x\n", (unsigned) tag - addr);
}

void rn_main(unsigned long magic, unsigned long mbinfo) {
   	tty_init();

    verify_grub2(magic, mbinfo);
}
