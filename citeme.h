/**
 * \file citeme.h
 * \brief CiteMe :)
 * \author Oleksandr
 * \author Burcin
 * 
 * BSD License
 */

#ifndef __CITE_ME_LIBRARY_PART_H__
#define __CITE_ME_LIBRARY_PART_H__

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief This structure is to be filled in by a library (data provider) and passed on to \ref RegisterCitation.
 */
struct CitationStruct
{
   const char* name;    /**< short library name. */
   const char* version; /**< library version string. */
   const char* license; /**< short library license. */
   const char* authors; /**< list of library authors. */
   const char* banner;  /**< banner of the library. */
   const char* bibitem; /**< BiBTex item. */
};


/**
 * \brief Specifies the kind of data application want to know about the library, to be used with \ref BannerFunction.
 */
enum BannerType
{
   GetName,          /**< library name or ID */
   GetAuthors,       /**< authors */
   GetBannerMessage, /**< banner message */
   GetBibItem,       /**< BibTex citation for the library */
};

typedef enum BannerType BannerType;

/**
 * \brief The function to be implemented in by a library (similar to \ref CitationStruct) and passed to \ref RegisterCitation.
 *
 * \param [in] _type The data specification. For possible values see \ref BannerType
 * 
 * \return string (a 0-terminating array of characters), containing the
 * requested data or \c NULL, if such information is not available.
 *  
 */ 
typedef const char* (*BannerFunction)(const BannerType _type); 


/** \brief input formats understandable by \ref RegisterCitation. */
enum CitationType
{
  ViaStuct,  /**< argument is (CitationStruct*) */	
  ViaBanner, /**< argument is BannerFunction */	
  Otherwise, /**< use some other method? */
};

/** \brief Possible return codes from \ref RegisterCitation. */
enum CitationError
{
   Ok = 0,              /**< Everything was fine */
   Error = -1,          /**< Something unexpectedly went wrong: bad luck... */
   ErrorWrongArgs = -2, /**< Are you trying to speak morse code? */
   ErrorDuplicate = -3, /**< Hey, you have been already cited... */
};

typedef struct CitationStruct CitationStruct;
typedef enum CitationType CitationType;
typedef enum CitationError CitationError;

#ifndef NO_CITATION_DATA
/**
 * \brief The Registrar' _only_ entry point. 
 * 
 * This global function is meant to be used by anyone willing to _provide_ a citation data. 
 * It must be exported from the _main_ application (the _only_ data _collecting_ party).
 * 
 * One can use it as follows (more can be found in \c citeme_provider.c):
 * 
 * \code
 * static const CitationStruct _about_me =
 * {
 *   "mylib", NULL, NULL, "me!",
 *   "\n\n\nHi, this is an example library, which wants some credits... Have Fun!\n\n\n",
 *   "@article{REF, title = {mylib}, year = {2011}, author = {Me}}"
 * };
 * CitationError ret = RegisterCitation(ViaStuct, &_about_me);
 * if( ret < Ok ) // Bad citation... Error code: ret... Help me!...
 * \endcode 
 *
 * Any _shady_ application may choose to ignore all the provided data
 * just by proving it, for example, as follows:
 * 
 * \code
 * #ifdef __cplusplus
 * extern "C" {
 * #endif
 *
 * CitationError RegisterCitation(const CitationType _type,...){ return Ok; }
 * 
 * #ifdef __cplusplus
 * }
 * #endif 
 * \endcode
 *
 * \note
 * We are also going to provide a legacy implemention for data collecting.
 *
 * \note
 * Note that the collector party should copy the strings returened/provided
 * by the library, whenever they are stored for later use.
 *
 * TODO: think about the following issues: 
 *   - variable argument list may prevent wrapping it easily... 
 *   - maybe a _variable_ (function pointer) would be better (e.g. due to Windows' limitations on dynamic libraries)?
 * 
 * \param [in] _type The citation format.
 * For possible values see \ref CitationType
 * 
 * \return Ok = 0 if successful, and negative value if there is a failure.
 * For possible codes see \ref CitationError
 * 
 */
extern CitationError RegisterCitation(const CitationType _type,...);
#else
/* This is an easy way to get rid of all this citation business, without changing your code too much... */
#define RegisterCitation(_type, ...) (Ok)
#endif /* NO_CITATION_DATA */


#ifdef ONLY_FOR_DOXYGEN
/**
 * One can use the following code in order to get rid of the _backward_ dependency by
 * ignoring any citation data, without changing any code:
 * 
 * \code
 * #define NO_CITATION_DATA
 * #include <citeme.h>
 * \endcode
 *
 * \note You should define \ref NO_CITATION_DATA \b before including \ref citeme.h!
 */
#define NO_CITATION_DATA
#endif /* ONLY_FOR_DOXYGEN */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CITE_ME_LIBRARY_PART_H__ */
