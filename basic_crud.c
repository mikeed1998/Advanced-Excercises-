#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256

typedef char*** MATRIX;

MATRIX createMatrix(int, int);
void printMatrix(MATRIX, int, int);
void freeMemory(MATRIX, int, int);
void updateMatrix(MATRIX, int, int);

int main(int argc, char *argv[])
{
	int x, y;
	MATRIX matrix;
	
	printf("X >>");
	scanf("%d", &x);
	printf("Y >>");
	scanf("%d", &y);
	
	matrix = createMatrix(x, y);
	printMatrix(matrix, x, y);
	updateMatrix(matrix, x, y);
	printMatrix(matrix, x, y);
	freeMemory(matrix, x, y);
	
	printf("\n\n");
	
	return 0;
}

MATRIX createMatrix(int _x, int _y)
{
	MATRIX matrix = (MATRIX)calloc(_x, sizeof(char**));
	char buffer[MAX_BUFFER] = {0};
	
	for(int i = 0; i < _x; i++) {
		*(matrix + i) = (char**)calloc(_y, sizeof(char*));
		for(int j = 0; j < _y; j++) {
			printf("pos[%d][%d] >>", i + 1, j + 1);
			scanf("%255s", buffer);
			*(*(matrix + i) + j) = (char*)malloc(sizeof(char) * MAX_BUFFER);
			strcpy(*(*(matrix + i) + j), buffer);
			memset(buffer, 0, sizeof(buffer));
		}
	}
	
	return matrix;
}

void printMatrix(MATRIX _matrix, int _x, int _y)
{
	for(int i = 0; i < _x; i++) {
		printf("\n");
		for(int j = 0; j < _y; j++) {
			printf("[%s]", *(*(_matrix + i) + j));
		}
	}
}

void freeMemory(MATRIX _matrix, int _x, int _y)
{
	for(int i = 0; i < _x; i++) {
		for(int j = 0; j < _y; j++)
			free(*(*(_matrix + i) + j));
		free(*(_matrix + i));
	}
	
	free(_matrix);
}

void updateMatrix(MATRIX matrix, int x_size, int y_size) {
    int target_x, target_y;
    char buffer[MAX_BUFFER] = {0};
    
    printf("\nPosicion a actualizar [x y] >> ");
    scanf("%d %d", &target_x, &target_y);
    
    if (target_x < 0 || target_x >= x_size || target_y < 0 || target_y >= y_size) {
        fprintf(stderr, "Error: Coordenadas fuera de rango\n");
        return;
    }
    
    printf("Nuevo valor para [%d][%d] >> ", target_x, target_y);
    scanf("%255s", buffer);
    
    char **fila = *(matrix + target_x);
    char **elemento = fila + target_y;
    
    size_t new_size = strlen(buffer) + 1;  // +1 para el '\0'
    
    if (*elemento == NULL || new_size > MAX_BUFFER) {
        char *new_ptr = (char *)realloc(*elemento, new_size);
        if (!new_ptr) {
            fprintf(stderr, "Error en realloc\n");
            return;
        }
        *elemento = new_ptr;
    }
    
    strcpy(*elemento, buffer);
    printf("¡Actualizado!\n");
}
















