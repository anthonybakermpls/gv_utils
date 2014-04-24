#include <stdio.h>




void print_header();
void print_body(int argc, char *argv[]);
void print_footer();

FILE *ofp;
char *mode = "r";
char o_file_0[]="listing.gv";

int main (int argc, char *argv[]) 
{
	
	ofp=fopen(o_file_0,"w");
	
	if(ofp==NULL){
		fprintf(stderr, "Can't open output file %s!\n", o_file_0);
		return(1);
	}

	
	/* 
	
	*/
	print_header();
	print_body(argc, argv);
	print_footer();
	
	
	

	

	fclose(ofp);

	return 0;

}



void print_header()
{
	char header[]="\
digraph g {\n\
rankdir=TB;\n\
size=\"8,5\";\n\
graph [fontname = \"consolas\"];\n\
node [fontname = \"consolas\"];\n\
edge [fontname = \"consolas\"];\n\
node  [shape = ellipse];\n";
					
	fprintf(ofp, "%s \n", header);					

}
void print_body(int argc, char *argv[])
{
	for(int i=1; i< argc-1; i++) /* skip first argument - program name */
	{
		fprintf(ofp, "n_%d[label=\"%s\"];\n",i, argv[i]);
	}
}
void print_footer()
{
	fprintf(ofp, "%s \n", "}");
}
