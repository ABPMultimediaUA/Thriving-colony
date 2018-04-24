#ifndef __DRV_TERRAIN_H__
#define __DRV_TERRAIN_H__

#include <vector>
#include <glm/glm.hpp>

/* We need a large enough index buffer to:
 *
 * 1. Ensure that we have room for the worse case scenario (all indices)
 * 2. Avoid stalling the GPU with updates to the index buffer.
 *
 * So we use two buffers that are twice the size of the worse case scenario.
 */
#define TER_TERRAIN_NUM_INDEX_BUFFERS 3
#define TER_TERRAIN_MAX_IB_BYTES (((TER_TERRAIN_VX - 1) * (TER_TERRAIN_VZ * 2) + (TER_TERRAIN_VX - 2) + (TER_TERRAIN_VZ - 2)) * sizeof(unsigned) * 2)
#define TER_TERRAIN_MAX_IB_INDICES (TER_TERRAIN_MAX_IB_BYTES / sizeof(unsigned))

#define TERRAIN(t, w, d) t->heights[(w) * t->depth + (d)]

typedef struct {
   float x0, x1, y0, y1, z0, z1;
} TerClipVolume;

typedef struct {
   int width, height, depth;
   float step;
   float *heights;

   float *vertices;
   unsigned num_vertices;

   unsigned *indices;
   unsigned num_indices;

   unsigned vao;
   unsigned vertex_buf;

   unsigned index_buf[TER_TERRAIN_NUM_INDEX_BUFFERS];
   unsigned ibuf_idx;
   unsigned ibuf_used;
   unsigned ibuf_cur_offset;

   glm::mat4 prev_mvp;
   bool prev_mvp_valid;
} TerTerrain;

TerTerrain *ter_terrain_new(unsigned width, unsigned depth, float step);
void ter_terrain_free(TerTerrain *t);

void ter_terrain_set_height(TerTerrain *t, unsigned w, unsigned d, float h);

float ter_terrain_get_height_at(TerTerrain *t, float x, float z);

void ter_terrain_set_heights_from_texture(TerTerrain *t, const char *path, float offset, float scale);
   
void ter_terrain_build_mesh(TerTerrain *t);

void ter_terrain_compute_clipped_indices(TerTerrain *t, TerClipVolume *clip,
                                         unsigned *count, size_t *offset);

float ter_terrain_get_width(TerTerrain *t);
float ter_terrain_get_height(TerTerrain *t);
float ter_terrain_get_depth(TerTerrain *t);

#endif
