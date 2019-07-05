/**
 * descriptor_tables_init.c - init gdt/idt
 * System sources under license MIT
 */

#include <system.h>
#include <kernel/ports.h>
#include <cpu/descriptors_table.h>
#include <cpu/isr.h>
#include <string.h>

extern void	gdt_flush(uint32_t);
extern void	idt_flush(uint32_t);
extern isr_t	interrupt_handlers_map[];

static void	__gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);
static void	__idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

gdt_entry_t	gdt_entries[5];
gdt_ptr_t	gdt_ptr;
idt_entry_t	idt_entries[256];
idt_ptr_t	idt_ptr;

void	install_gdt() {
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base = (uint32_t)&gdt_entries;

	__gdt_set_gate(NULL_SEGMENT, 0, 0, 0, 0);
	__gdt_set_gate(CODE_SEGMENT, 0, 0xffffffff ,0x9a, 0xcf);
	__gdt_set_gate(DATA_SEGMENT, 0, 0xffffffff ,0x92, 0xcf);
	__gdt_set_gate(USER_MODE_CODE_SEGMENT, 0, 0xffffffff ,0xfa, 0xcf);
	__gdt_set_gate(USER_MODE_DATA_SEGMENT, 0, 0xffffffff ,0xf2, 0xcf);
	gdt_flush((uint32_t)&gdt_ptr);
}

void	install_idt() {
	idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
	idt_ptr.base = (uint32_t)&idt_entries;

	memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

	port_write_byte(0x20, 0x11);
	port_write_byte(0xa0, 0x11);
	port_write_byte(0x21, 0x20);
	port_write_byte(0xa1, 0x28);
	port_write_byte(0x21, 0x04);
	port_write_byte(0xa1, 0x02);
	port_write_byte(0x21, 0x01);
	port_write_byte(0xa1, 0x01);
	port_write_byte(0x21, 0x0);
	port_write_byte(0xa1, 0x0);

	__idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8e);
	__idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8e);
	__idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8e);
	__idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8e);
	__idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8e);
	__idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8e);
	__idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8e);
	__idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8e);
	__idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8e);
	__idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8e);
	__idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8e);
	__idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8e);
	__idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8e);
	__idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8e);
	__idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8e);
	__idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8e);
	__idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8e);
	__idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8e);
	__idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8e);
	__idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8e);
	__idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8e);
	__idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8e);
	__idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8e);
	__idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8e);
	__idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8e);
	__idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8e);
	__idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8e);
	__idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8e);
	__idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8e);
	__idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8e);
	__idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8e);
	__idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8e);
	__idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8e);
	__idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8e);
	__idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8e);
	__idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8e);
	__idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8e);
	__idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8e);
	__idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8e);
	__idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8e);
	__idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8e);
	__idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8e);
	__idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8e);
	__idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8e);
	__idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8e);
	__idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8e);
	__idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8e);
	__idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8e);

	idt_flush((uint32_t)&idt_ptr);
	memset(&interrupt_handlers_map, 0, sizeof(isr_t) * 256);
}

static void	__gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
	gdt_entries[num].base_low = (base & 0xffff);
	gdt_entries[num].base_middle = (base >> 16) & 0xff;
	gdt_entries[num].base_hight = (base >> 24) & 0xff;

	gdt_entries[num].limit_low = (limit & 0xffff);
	gdt_entries[num].granularity = (limit >> 16) & 0x0f;

	gdt_entries[num].granularity |= gran & 0xf0;
	gdt_entries[num].access = access;
}

static void	__idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
	idt_entries[num].base_lo = base & 0xffff;
	idt_entries[num].base_hi = (base >> 16) & 0xffff;
	idt_entries[num].sel = sel;
	idt_entries[num].always0 = 0;
	idt_entries[num].flags = flags;
	// idt_entries[num].flags = flags | 0x60; // uncoment for ring 3
}

