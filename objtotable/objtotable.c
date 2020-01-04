#include <stdio.h>

int vpl;
int ipl;
int verts[8192];
int inds[8192];

int main()
{
	int i;
	FILE * f = fopen( "bananas.obj", "r" );
	if( !f )
	{
		fprintf( stderr, "Error: Bananas.\n" );
		return 0;
	}

	while( !feof( f ) && !ferror(f ) )
	{
		char line[1024];
		int c;
		int lpl = 0;
		while( (c = fgetc( f )) != EOF )
		{
			line[lpl] = c;
			if( c == '\n' ) break;
			lpl++;
		}
		line[lpl] = 0;
		char dump[1024];
		if( strncmp( line, "v ", 2 ) == 0 )
		{
			float vert[3];
			sscanf( line, "%s %f %f %f\n", dump, vert+0, vert+1, vert+2 );
			i = 0;
			verts[i+vpl] = vert[i] * 100;  i++;
			verts[i+vpl] = vert[i] * 100; i++;
			verts[i+vpl] = vert[i] * 100;  i++;
			vpl += 3;
		}
		if( strncmp( line, "f ", 2 ) == 0 )
		{
			char c1[128];
			char c2[128];
			char c3[128];
			sscanf( line, "%s %s %s %s\n", dump, c1, c2, c3 );
			inds[ipl++] = atoi( c1 )-1;
			inds[ipl++] = atoi( c2 )-1;
			inds[ipl++] = atoi( c3 )-1;
		}
	}
	printf( "int16_t verts_bananas[%d] = {\n", vpl );
	for( i = 0; i < vpl; i+=3 )
		printf( "%4d,%4d,%4d,  %c", verts[i+0], verts[i+1], verts[i+2], ((i-1)&3)?' ':'\n' );
	printf( "};\n" );
	printf( "const uint8_t indices_bananas[%d] = {\n", vpl );
	for( i = 0; i < ipl; i+=3 )
		printf( "%3d,%3d,%3d,  %c", inds[i+0], inds[i+1], inds[i+2], ((i-1)&3)?' ':'\n' );
	printf( "};\n" );
}

