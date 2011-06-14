/*
 * CiteMe :)
 * BSD License
 * Authors: Oleksandr and Burcin
 */

/* some usefull citation :) http://www.parashift.com/c++-faq-lite/mixing-c-and-cpp.html */


#ifndef __CITE_ME_LIBRARY_PART_H__
#define __CITE_ME_LIBRARY_PART_H__

#ifdef __cplusplus
extern "C"
{
#endif

// #include "citeme/common.h" // TODO: both enums should be in this common.h

/** The structure to be filled in by a library and passed to \ref RegisterCitation */ 
typedef struct CitationStruct
{
   const char* name; /**< short library name*/
   const char* version; /**< library version string */
   const char* license; /**< short library license */
   const char* authors; /**< authors */
   const char* banner; /**< banner of the library */
   const char* bibitem; /**< BiBTex item */
} CitationStruct;
   

   
/** Cpecifies the kind of date application want to know about the library, to be used with \ref BannerFunction */
typedef enum BannerType
{
   GetName, /**< library name or ID */
   GetAuthors, /**< authors */
   GetBannerMessage, /**< banner message */
   GetBibItem /**< BibTex citation for the library */
} BannerType;
     
/** The structure to be filled in by a library and passed to \ref RegisterCitation */ 
typedef const char* (*BannerFunction)( const BannerType );

   
   
/** the return codes returned by \ref RegisterCitation */
typedef enum CitationError
{
   Ok = 0, /**< Everything was fine */
   Error = -1, /** Something unexpectedly went wrong: bad luck... */
   ErrorWrongArgs = -2, /** Are you trying to speak morse code? */
   ErrorDuplicate = -3 /** Hey, you have been already cited... */
} CitationError;


/** input formats understandable by \ref RegisterCitation */
typedef enum CitationType
{
   ViaStuct, /**< use a struct */	
   ViaBanner, /**< use a banner function */	
   Otherwise /**< use some other method? */
} CitationType;
  
   
/**
 * Function to be used by anyone willing to report a citation. 
 * It must be implemented _once_ and exported by the _main_ calling part: the application.
 * 
 * Note that the application should copy the strings returened/provided by the library for later use.
 * 
 * TODO: think about the following issues:
 *  1. variable argument list may prevent wrapping it?
 *  2. maybe a _variable_ (function pointer) would be better (e.g. due to Windows' limitations on dynamic libraries)?
 * 
 * \param [in] _type The citation format. see \ref CitationType for possible types.
 * \returns Ok = 0 if successful, and negative value if there is a failure. see \ref CitationErrors for possible codes
 *  */
extern CitationError RegisterCitation( const CitationType _type, ... );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CITE_ME_LIBRARY_PART_H__ */
