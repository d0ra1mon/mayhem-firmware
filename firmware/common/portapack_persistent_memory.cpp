/*
 * Copyright (C) 2015 Jared Boone, ShareBrained Technology, Inc.
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "portapack_persistent_memory.hpp"

#include "hal.h"

#include <algorithm>
#include <utility>

namespace portapack {
namespace persistent_memory {

/* TODO: This is widely applicable. Factor this to somewhere useful. */
template<class T>
struct range_t {
	const T minimum;
	const T maximum;

	const T& clip(const T& value) const {
		return std::max(std::min(value, maximum), minimum);
	}

	void reset_if_outside(T& value, const T& reset_value) const {
		if( (value < minimum ) ||
			(value > maximum ) ) {
			value = reset_value;
		}
	}
};

using tuned_frequency_range_t = range_t<rf::Frequency>;
constexpr tuned_frequency_range_t tuned_frequency_range { rf::tuning_range.min, rf::tuning_range.max };
constexpr rf::Frequency tuned_frequency_reset_value { 858750000 };

using ppb_range_t = range_t<ppb_t>;
constexpr ppb_range_t ppb_range { -99000, 99000 };
constexpr ppb_t ppb_reset_value { 0 };

using afsk_freq_range_t = range_t<int32_t>;
constexpr afsk_freq_range_t afsk_freq_range { 1, 60 };
constexpr int32_t afsk_mark_reset_value { 12 };
constexpr int32_t afsk_space_reset_value { 22 };

using afsk_bitrate_range_t = range_t<int32_t>;
constexpr afsk_bitrate_range_t afsk_bitrate_range { 600, 9600 };
constexpr int32_t afsk_bitrate_reset_value { 1200 };

/* struct must pack the same way on M4 and M0 cores. */
struct data_t {
	// General config
	int64_t tuned_frequency;
	int32_t correction_ppb;
	
	// AFSK modem
	int32_t afsk_mark_freq;
	int32_t afsk_space_freq;		// Todo: optimize size, only 256 bytes of NVRAM !
	int32_t afsk_bitrate;
	uint32_t afsk_config;
	
	// Play dead unlock
	uint32_t playing_dead;
	uint32_t playdead_sequence;
};

static_assert(sizeof(data_t) <= 0x100, "Persistent memory structure too large for VBAT-maintained region");

static data_t* const data = reinterpret_cast<data_t*>(LPC_BACKUP_REG_BASE);

rf::Frequency tuned_frequency() {
	tuned_frequency_range.reset_if_outside(data->tuned_frequency, tuned_frequency_reset_value);
	return data->tuned_frequency;
}

void set_tuned_frequency(const rf::Frequency new_value) {
	data->tuned_frequency = tuned_frequency_range.clip(new_value);
}

ppb_t correction_ppb() {
	ppb_range.reset_if_outside(data->correction_ppb, ppb_reset_value);
	return data->correction_ppb;
}

void set_correction_ppb(const ppb_t new_value) {
	data->correction_ppb = ppb_range.clip(new_value);
}

int32_t afsk_mark_freq() {
	afsk_freq_range.reset_if_outside(data->afsk_mark_freq, afsk_mark_reset_value);
	return data->afsk_mark_freq;
}

void set_afsk_mark(const int32_t new_value) {
	data->afsk_mark_freq = afsk_freq_range.clip(new_value);
}

int32_t afsk_space_freq() {
	afsk_freq_range.reset_if_outside(data->afsk_space_freq, afsk_space_reset_value);
	return data->afsk_space_freq;
}

void set_afsk_space(const int32_t new_value) {
	data->afsk_space_freq = afsk_freq_range.clip(new_value);
}

int32_t afsk_bitrate() {
	afsk_bitrate_range.reset_if_outside(data->afsk_bitrate, afsk_bitrate_reset_value);
	return data->afsk_bitrate;
}

void set_afsk_bitrate(const int32_t new_value) {
	data->afsk_bitrate = afsk_bitrate_range.clip(new_value);
}

uint32_t afsk_config() {
	return data->afsk_config;
}

void set_afsk_config(const uint32_t new_value) {
	data->afsk_config = new_value;
}

uint32_t playing_dead() {
	return data->playing_dead;
}

void set_playing_dead(const uint32_t new_value) {
	data->playing_dead = new_value;
}

uint32_t playdead_sequence() {
	return data->playdead_sequence;
}

void set_playdead_sequence(const uint32_t new_value) {
	data->playdead_sequence = new_value;
}

} /* namespace persistent_memory */
} /* namespace portapack */