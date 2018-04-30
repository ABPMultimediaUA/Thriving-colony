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

#define TERRAIN(t, w, d) t->heights[(w) * t->depth + (d)]

typedef struct {
   float x0, y0, z0;
   float x1, y1, z1;
} TerClipVolume;

typedef struct {
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
} TerTriangle;

typedef struct {
   int width, height, depth;
   
   float step;
   
   float *heights;

   float *vertices;
   unsigned num_vertices;

   short *indices;
   unsigned num_indices;

   TerTriangle *triangles;
   unsigned num_triangles;
} TerTerrain;

TerTerrain *ter_terrain_new(unsigned width, unsigned depth, float step);
void ter_terrain_free(TerTerrain *t);

void ter_terrain_set_height(TerTerrain *t, unsigned w, unsigned d, float h);

float ter_terrain_get_height_at(TerTerrain *t, float x, float z);

void ter_terrain_set_heights_from_texture(TerTerrain *t, const char *path, float offset, float scale);

void ter_terrain_set_triangles_from_indices(TerTerrain *t);
   
void ter_terrain_build_mesh(TerTerrain *t);

void ter_terrain_compute_clipped_indices(TerTerrain *t, TerClipVolume *clip,
                                         unsigned *count, size_t *offset);

float ter_terrain_get_width(TerTerrain *t);
float ter_terrain_get_height(TerTerrain *t);
float ter_terrain_get_depth(TerTerrain *t);

#endif
