/* 
 * TODO: 
 * - insert error detection
 * - subdir search node decls
 * - 
 */

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h> // basename
#include <dirent.h> // 

#ifdef __cplusplus
extern "C" {
#endif




void print_header();
void print_body(int argc, char *argv[]);
void print_footer();

void print_node_decs(int argc, char *argv[]);
void print_edges(int argc, char *argv[]);
char * check_string_for_include(char s[]);
char * parse_include_directive(char s[]);


FILE *ofp;
char *mode = "r";
char o_file_0[]="/home/e29988/Working/C/listing.gv"; /* uh */

int main (int argc, char *argv[]) 
{
	printf("Analyzing...\n");
	ofp=fopen(o_file_0,"w");
	if(ofp==NULL){
		fprintf(stderr, "Can't open output file %s!\n", o_file_0);
		return(1);
	}
	
	
	/* sections of our gv file */
	print_header();
	print_body(argc, argv);
	print_footer();
	
	
	
	
	fclose(ofp);
	printf("Generated graph.\n");
	
	return 0;
}



void print_header()
{
	char header[]="\
digraph g {\n\
rankdir=TB;\n\
size=\"11,11\";\n\
graph [fontname = \"consolas\"];\n\
node [fontname = \"consolas\"];\n\
edge [fontname = \"consolas\"];\n\
node  [shape = ellipse];\n";
					
	fprintf(ofp, "%s \n", header);					

}
void print_body(int argc, char *argv[])
{
	print_node_decs(argc,argv); /* print files in current dir */
	print_edges(argc,argv);     /* print edges of all files found when parsing */
	
								/* problem: files found in parsing are not in current dir and therefore do not have node decls */
}
void print_footer()
{
	fprintf(ofp, "%s \n", "}");
}


void print_node_decs(int argc, char *argv[])
{	
	fprintf(ofp, "/* Node declarations */\n");
	
	char * pch=NULL;
	char * temp=NULL;
	char str[128];
	for(int i=1; i< argc-1; i++) /* skip first argument - program name */
	{
		strcpy(str,argv[i]); 
		temp=str;
		pch = strtok(temp,".");
		fprintf(ofp, "%s[label=\"%s\"];\n",pch,argv[i]);
	}
	fprintf(ofp, "\n");
}

void print_edges(int argc, char *argv[])
{
	fprintf(ofp, "/* Edges */\n");

	int lc=0; /* line counter */
	char line[1024];
	
	FILE *ifile;
	char *mode="r";
	
	char * pch=NULL;
	char * pch2=NULL;
	char * temp=NULL;
	char * temp2=NULL;
	char str[128];
	char str2[128];
	
	for(int i=1; i< argc-1; i++) /* skip first argument - program name */
	{
		strcpy(str,argv[i]); 
		temp=str;
		pch = strtok(temp,".");
		
		ifile=fopen(argv[i],mode);
		if(ifile==NULL){ 
			fprintf(stderr, "Can't open input file in.list!\n");
			return;
		}
		printf("Checking file %s\n", argv[i]);
		
		while(fgets(line, 1024, ifile) != NULL)//while (fscanf(ifile, "%s", line) != EOF) 
		{	
			char* search=NULL;
			search=check_string_for_include(line);
			if(search!=NULL){
				strcpy(str2,parse_include_directive(search)); 
				temp2=basename(str2); // strip path
				pch2 = strtok(temp2,".");
				fprintf(ofp, "%s->%s;\n",pch,pch2);
			}
			lc=lc+1;
		}	
		lc=0;
		fclose(ifile);
	}
}



/* 
 * input: line of file
 * output: "#include <filename.h>" if we find an include directive otherwise NULL
 */
char * check_string_for_include(char s[])
{
	if (strncmp(s,"#include",8) == 0)
	{
	  return s;
	}
	else return NULL;
}


/* 
 * input: string like "#include <sys/filename.h>"
 * output: filename.h
 */
char * parse_include_directive(char s[])
{
	char *str=s;
	char * pch;
	pch = strtok (str,"<");
	pch = strtok (NULL, ">");
	return pch;
}




#ifdef __cplusplus
}
#endif
