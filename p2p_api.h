#pragma once

#ifndef P2P_API_H_
#define P2P_API_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Notation: [Xa-Ya-Za]
 *
 * [] denotes a machine word of the specified endianness.  Xa-Ya-Za denote
 * component X, Y, and Z packed in the word, with bit depths a, b, c, in order
 * from MSB to LSB.  Padding bits are represented by the component '!'.
 */
enum p2p_packing {
	/** [R8-G8-B8] */
	p2p_rgb24_be,
	p2p_rgb24_le,
	p2p_rgb24,
	/** [A8-R8-G8-B8] */
	p2p_argb32_be,
	p2p_argb32_le,
	p2p_argb32,
	/** [A8-Y8-U8-V8] */
	p2p_ayuv_be,
	p2p_ayuv_le,
	p2p_ayuv,
	/** [R16-G16-B16] */
	p2p_rgb48_be,
	p2p_rgb48_le,
	p2p_rgb48,
	/** [A16-R16-G16-B16] */
	p2p_argb64_be,
	p2p_argb64_le,
	p2p_argb64,
	/** [A2-R10-G10-B10] */
	p2p_rgb30_be,
	p2p_rgb30_le,
	p2p_rgb30,
	/** [A2-V10-Y10-U10] */
	p2p_y410_be,
	p2p_y410_le,
	p2p_y410,
	/** [A16-V16-Y16-U16] */
	p2p_y416_be,
	p2p_y416_le,
	p2p_y416,
	/** [Y8] [U8] [Y8] [V8] */
	p2p_yuy2,
	/** [U8] [Y8] [V8] [Y8] */
	p2p_uyvy,
	/** [Y10-!6] [U10-!6] [Y10-!6] [V10-!6] */
	p2p_y210_be,
	p2p_y210_le,
	p2p_y210,
	/** [Y16] [U16] [V16] [Y16] */
	p2p_y216_be,
	p2p_y216_le,
	p2p_y216,
	/** [!2-V10-Y10-U10] [!2-Y10-U10-Y10] [!2-U10-Y10-V10] [!2-Y10-V10-Y10] */
	p2p_v210_be,
	p2p_v210_le,
	p2p_v210,
	/** [U16] [Y16] [V16] [Y16] */
	p2p_v216_be,
	p2p_v216_le,
	p2p_v216,
	/** [U8-V8] */
	p2p_nv12_be,
	p2p_nv12_le,
	p2p_nv12,
	/** [U10-X6-V10-X6] */
	p2p_p010_be,
	p2p_p010_le,
	p2p_p010,
	/** [U16-V16] */
	p2p_p016_be,
	p2p_p016_le,
	p2p_p016,
	/** [U10-X6-V10-X6] */
	p2p_p210_be,
	p2p_p210_le,
	p2p_p210,
	/** [U16-V16] */
	p2p_p216_be,
	p2p_p216_le,
	p2p_p216,

	p2p_packing_max,
};

struct p2p_buffer_param {
	const void *src[4];
	void *dst[4];
	ptrdiff_t src_stride[4];
	ptrdiff_t dst_stride[4];
	unsigned width;
	unsigned height;
	enum p2p_packing packing;
};

/** Pack/unpack a range of pixels from a scanline. */
typedef void (*p2p_unpack_func)(const void *src, void * const dst[4], unsigned left, unsigned right);
typedef void (*p2p_pack_func)(const void * const src[4], void *dst, unsigned left, unsigned right);

/** Select a line pack/unpack function. */
p2p_unpack_func p2p_select_unpack_func(enum p2p_packing packing);
p2p_pack_func p2p_select_pack_func(enum p2p_packing packing);


/** When processing formats like NV12, ignore the unpacked plane. */
#define P2P_SKIP_UNPACKED_PLANES (1UL << 0)

/** Helper function to pack/unpack between memory locations. */
void p2p_unpack_frame(const struct p2p_buffer_param *param, unsigned long flags);
void p2p_pack_frame(const struct p2p_buffer_param *param, unsigned long flags);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* P2P_API_H_ */
