// license:BSD-3-Clause
// copyright-holders:Juergen Buchmueller
/*****************************************************************************
 *
 *   Xerox AltoII memory mapped I/O keyboard
 *
 *****************************************************************************/
#include "emu.h"
#include "alto2cpu.h"

/**
 * @brief read the keyboard address matrix
 *
 * @param addr memory mapped I/O address to be read
 * @return keyboard matrix value for address modulo 4
 */
uint16_t alto2_cpu_device::kbd_ad_r(offs_t offset)
{
	uint16_t data = m_kb_read_callback(offset & 3);
	m_kbd.matrix[offset & 03] = data;
	if (!machine().side_effects_disabled()) {
		LOG((this,LOG_KBD,2,"    read KBDAD+%o (%#o)\n", offset & 3, data));
	}
	if (0 == (offset & 3) && (m_kbd.bootkey != 0177777)) {
		if (!machine().side_effects_disabled()) {
			LOG((this,0,2,"  boot keys (%#o & %#o)\n", data, m_kbd.bootkey));
		}
		data &= m_kbd.bootkey;
		m_kbd.bootkey = 0177777;
	}
	return data;
}

void alto2_cpu_device::init_kbd(uint16_t bootkey)
{
	m_kbd.bootkey = bootkey;
}

void alto2_cpu_device::exit_kbd()
{
	// nothing to do yet
}

void alto2_cpu_device::reset_kbd()
{
	m_kbd.matrix[0] = 0177777;
	m_kbd.matrix[1] = 0177777;
	m_kbd.matrix[2] = 0177777;
	m_kbd.matrix[3] = 0177777;
}
