#ifndef STRUCTS
#define STRUCTS

struct vec3_t {											//t suffix refers to type
	float x, y, z;
};

struct vec4_t
{
	float x, y, z, w;
};

struct enemy {
	vec3_t pos;
	DWORD enemyBase;
	int hp, team;
	char name[20];
};


#endif

