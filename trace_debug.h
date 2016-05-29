


//#define __DEBUG__     //  debug log dump

#ifdef __DEBUG__
 
  #define trace DoTrace
  #define trace1 DoTrace

#else
  #define trace  
  #define trace1  
  #define __TRACE_DEBUG__
#endif


#include "stdlib.h"
static inline void DoTrace(char *fmt, ...);
static void fileappend( char* filename,  char* buf);


#ifndef __TRACE_DEBUG__
#define __TRACE_DEBUG__

/* {{{ trace */

static inline void DoTrace(char *fmt, ...)
{
	va_list ap;
	char buf[4096];

	//sprintf(buf, "T=%08x ", tsrm_thread_id());
	//OutputDebugString(buf);

	//fileappend("c:\\phpdebuglog.txt", buf);
	
	va_start(ap, fmt);	
	vsnprintf(buf, sizeof(buf), fmt, ap);
	OutputDebugString(buf);
	fileappend("c:\\phpdebuglog.txt", buf);
	va_end(ap);
}

/* }}} */
#endif // __TRACE_DEBUG__


#ifndef __STRING_TRIM__
#define __STRING_TRIM__



static void trim(char * src)
{
     unsigned int i = 0;
     char *begin = src;
     
	 for(i = 0; i < strlen(src) ;  i++){
           if(src[i] != 0x20){
              break;
            }else{
                begin++;
            }
      }

     trace1("\r\n %s  src=%d, begin= %d", src, src, begin);

      for(i = strlen(src)-1; i >= 0;  i--){
           if(src[i] != 0x20){
              break;
            }else{
                  src[i] = '\0';
            }
      }

      for(i = 0; i < strlen(begin);  i++){
         src[i] = begin[i];          
      }
      src[i] = 0x00;  
 
     return ;
}

 

static char* replace(char* src,char* seps)
{
  char* token=NULL;
   char * buf;
   int len = strlen(src);
   buf = (char*)malloc(len);
   memset(buf,0,len);
  /* Establish string and get the first token: */
   token = strtok(src, seps);
   while( token != NULL )
   {
      /* While there are tokens in "string" */
     
      strcat(buf,token);
      /* Get next token: */
      token = strtok( NULL, seps );
   }
   strcpy(src,buf);
   free(buf);
   return src;
}



static  char* getfilecontents( char* filename,  char* buf, unsigned int len)
{
	
	FILE *fp;
    fp=fopen(filename,"r");
	if(fp==NULL)
	{
	  return NULL;
	}
    char line[128];
    memset(buf,0, len);
    while(!feof(fp))
	{
	    
		fgets(line,128,fp);
        if(strlen(buf) +strlen(line) >= len) break;
		strcat(buf,line);
	}
   
	return buf;
}

static void fileappend( char* filename,  char* buf)
{
	
	FILE *fp;
 fp=fopen(filename,"a");
	if(fp!=NULL)
	{
	 //fwrite(  buf, strlen(buf),1, fp);
	 fputs(buf,fp)  ;
     fclose(fp);
	 
	}
	 

}

#endif // __STRING_TRIM__





