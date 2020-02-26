/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the  "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#if !defined(XALAN_CAPI_HEADER_GUARD_1357924680)
#define XALAN_CAPI_HEADER_GUARD_1357924680



#include <xalanc/XalanTransformer/XalanTransformerDefinitions.hpp>



/**
 * This is a simple C interface for the class XalanTransformer. It's 
 * the user's responsibility to call XalanInitialize() before making
 * any other API calls, and to call XalanTerminate() when finished
 * with the API.
 *
 * After calling XalanTransformToData or XalanTransformToDataCSS, the user   
 * should call XalanFreeData to release the memory allocated by that 
 * operation.
 */
#if defined(__cplusplus)
extern "C"
{
#endif

    /**
     * Handle used to store the address of XalanTransformer instance.
     */
    typedef void*           XalanHandle;

    /**
     * Handle used to store the address of Compiled Stylesheet instance.
     */
    typedef const void*     XalanCSSHandle;

    /**
     * Handle used to store the address of Parsed Source instance.
     */
    typedef const void*     XalanPSHandle;

    /**
     * This is a typedef to work around limitations with
     * the XALAN_TRANSFORMER_EXPORT_FUNCTION macro.
     */
    typedef const char*     XalanCCharPtr;

    /**
     * This is a typedef for characters encoded in UTF-16.
     */
    typedef XMLCh           XalanUTF16Char;

    /**
     * Initialize Xerces and Xalan.
     *
     * Should be called only once per process before making
     * any other API calls.
     *
     * @return 0 if successful, -1 if initialization fails.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
#if defined(__cplusplus)
    XalanInitialize();
#else
    XalanInitialize(void);
#endif

    /**
     * Terminate Xalan and Xerces.
     *
     * Should be called only once per process after deleting all
     * instances of XalanTransformer.
     *
     * Once a process has called this function, it cannot use the
     * API until another call to XalanInitialize has been made.
     * 
     * Optionally, if the ICU has been integrated, this will
     * call the ICU clean up function.  This must only be done
     * if the ICU will no longer be used by the process, since
     * the ICU will no longer be in a usable state.  See the
     * ICU documentation for more details.
     *
     * This is handy when using leak-detection software, as all
     * static data allocated by Xalan (and optionally, the ICU)
     * will be freed.
     *
     * @param fCleanUpICU If true, call the ICU clean up function.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(void)
    XalanTerminate(int  fCleanUpICU);

    /**
     * Create a XalanTransformer instance.
     *
     * @return  the XalanTransformer handle
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(XalanHandle)
    CreateXalanTransformer();


    /**
     * Delete a XalanTransformer instance.
     *
     * @param theXalanHandle The XalanTransformer to destroy.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(void)
    DeleteXalanTransformer(XalanHandle  theXalanHandle);

    /**
     * Transform the XML source tree to the given result file.
     * The processor will apply the stylesheet file to the input
     * file and write the transformation result to a new output file.
     *
     * @param theXMLFileName    The file name of the XML document.
     * @param theXSLFileName    The file name of the stylesheet XML document.
     * @param theOutFileName    The file name for the output.
     * @param theXalanHandle    The handle of a XalanTransformer instance.
     * @return  0 for success
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
    XalanTransformToFile(
                const char*     theXMLFileName,
                const char*     theXSLFileName,
                const char*     theOutFileName,
                XalanHandle     theXalanHandle);

    /**
     * Transform the XML source tree to the given result file.
     * The processor will apply the compiled stylesheet to the input
     * file and write the transformation result to a new output file.
     *
     * @param theParsedSource   The handle of a parsed source
     * @param theCSSHandle      The handle of a compiled stylesheet 
     * @param theOutFileName    The file name for the output.
     * @param theXalanHandle    The handle of a XalanTransformer instance.
     * @return  0 for success
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
    XalanTransformToFilePrebuilt(
            XalanPSHandle   theParsedSource,
            XalanCSSHandle  theCSSHandle,
            const char*     theOutFileName,
            XalanHandle     theXalanHandle);

    /**
     * Transform the XML source tree to a dynamically allocated buffer.
     * The processor will apply the stylesheet file to the input file
     * and assign the address of the dynamically allocated result to a
     * user-supplied pointer. The user must call XalanFreeData with this
     * pointer to free the memory.
     *
     * @param theXMLFileName    The file name of the XML document.
     * @param theXSLFileName    The file name of the stylesheet XML document.
     * @param theOutput         a pointer to a char*
     * @param theXalanHandle    handle of XalanTransformer instance.
     * @return  0 for success
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
    XalanTransformToData(
            const char*     theXMLFileName,
            const char*     theXSLFileName,
            char**          theOutput,
            XalanHandle     theXalanHandle);

    /**
     * Transform the XML source tree to a dynamically-allocated buffer.
     * The processor will apply the compiled stylesheet to the input file
     * and assign the address of the dynamically allocated result to a 
     * user supplied pointer. The user must call XalanFreeData with this 
     * pointer to free the memory.
     *
     * @param theParsedSource   The handle of a parsed source
     * @param theCSSHandle      The handle of compiled stylesheet
     * @param theOutput         a pointer to a char*
     * @param theXalanHandle    handle of XalanTransformer instance.
     * @return  0 for success
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
    XalanTransformToDataPrebuilt(
                XalanPSHandle   theParsedSource,
                XalanCSSHandle  theCSSHandle,
                char**          theOutput,
                XalanHandle     theXalanHandle);

    /**
     * Free memory allocated as a result of calling
     * XalanTransformToData.
     *
     * @param theData The address of character data.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(void)
    XalanFreeData(char*     theData);

    /**
     * Transform the XML source tree to a callback function.
     * The processor will apply the stylesheet file to the input file
     * and allocate the transformation result to a callback function
     * in pre-allocated blocks. Once the transformation is complete,
     * a second callback, to flush the buffer, is called. You can pass
     * in NULL if you do not wish to implement a flush callback. Xalan
     * will release any memory allocated upon termination, and data passed
     * to the callback is not guaranteed to be null terminated.
     *
     * See XalanTransformerDefinitions.hpp for more details.
     *
     * @param theXMLFileName    The file name of XML input source
     * @param theXSLFileName    The file name of stylesheet source
     * @param theXalanHandle    The handle of a XalanTransformer instance.
     * @param theOutputHandle   A void pointer passed through to callback.
     * @param theOutputHandler  A user-defined callback function pointer.
     * @param theFlushHandler   A user-defined callback function pointer, which can be null.
     * @return  0 for success
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int) 
    XalanTransformToHandler(
                const char*             theXMLFileName,
                const char*             theXSLFileName,
                XalanHandle             theXalanHandle,
                void*                   theOutputHandle,
                XalanOutputHandlerType  theOutputHandler,
                XalanFlushHandlerType   theFlushHandler);

    /**
     * Transform the XML source tree to a callback function.
     * The processor will apply the compiled stylesheet to the input file
     * and allocate the transformation result to a callback function
     * in pre-allocated blocks. Once the transformation is complete,
     * a second callback, to flush the buffer, is called. You can pass
     * in NULL if you do not wish to implement a flush callback. Xalan
     * will release any memory allocated upon termination, and data passed
     * to the callback is not guaranteed to be null terminated.
     * 
     * See XalanTransformerDefinitions.hpp for more details.
     *
     * @param thePSHandle       The handle of parsed source
     * @param theCSSHandle      The handle of compiled stylesheet 
     * @param theXalanHandle    The handle of XalanTransformer instance.
     * @param theOutputHandle   A void pointer passed through to callback.
     * @param theOutputHandler  A user-defined callback function pointer.
     * @param theFlushHandler   A user-defined callback function pointer, which can be null.
     * @return  0 for success 
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
    XalanTransformToHandlerPrebuilt(
                XalanPSHandle           thePSHandle,
                XalanCSSHandle          theCSSHandle,
                XalanHandle             theXalanHandle,
                void*                   theOutputHandle,
                XalanOutputHandlerType  theOutputHandler,
                XalanFlushHandlerType   theFlushHandler);

    /**
     * Creates a compiled stylesheet.
     *
     * @param theXSLFileName    The file name of stylesheet source
     * @param theXalanHandle    The handle of XalanTransformer instance.
     * @param theCSSHandle      a pointer to a XalanCSSHandle
     * @return 0 for success.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
    XalanCompileStylesheet(
            const char*         theXSLFileName,
            XalanHandle         theXalanHandle,
            XalanCSSHandle*     theCSSHandle);

    /**
     * Creates a compiled stylesheet.
     *
     * @param theXSLFileName The stream that contains the stylesheet xml
     * @param theXSLStreamLength The length of the stream.
     * @param theXalanHandle handle of XalanTransformer instance.
     * @param theCSSHandle a pointer to a XalanCSSHandle
     * @return 0 for success.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
    XalanCompileStylesheetFromStream(
            const char*         theXSLStream,
            unsigned long       theXSLStreamLength,
            XalanHandle         theXalanHandle,
            XalanCSSHandle*     theCSSHandle);

    /**
     * Destroys a compiled stylesheet.
     *
     * @param theCSSHandle      The handle of the compiled stylesheet.
     * @param theXalanHandle    The handle of XalanTransformer instance.
     * @return 0 for success
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
    XalanDestroyCompiledStylesheet(
            XalanCSSHandle  theCSSHandle,
            XalanHandle     theXalanHandle);

    /**
     * Parse source document.
     *
     * @param theXMLFileName The name of the file containing the source document
     * @param theXalanHandle The handle of XalanTransformer instance.
     * @param thePSHandle A pointer to a XalanPSHandle
     * @return 0 for success.
     */ 
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
    XalanParseSource(
            const char*     theXMLFileName,
            XalanHandle     theXalanHandle,
            XalanPSHandle*  thePSHandle);

    /**
     * Parse source document from a stream.
     *
     * @param theXMLStream The stream that contains the source xml
     * @param theXSLStreamLength The length of the stream
     * @param theXalanHandle The handle of XalanTransformer instance
     * @param thePSHandle A pointer to a XalanPSHandle
     * @return 0 for success.
     */ 
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
    XalanParseSourceFromStream(
            const char*     theXMLStream,
            unsigned long   theXMLStreamLength,
            XalanHandle     theXalanHandle,
            XalanPSHandle*  thePSHandle);

    /**
     * Destroys a parsed source.
     * a file name, a stream or a root node.
     *
     * @param thePSHandle       The handle of parsed source
     * @param theXalanHandle    The handle of XalanTransformer instance.
     * @return 0 for success
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(int)
    XalanDestroyParsedSource(
            XalanPSHandle   thePSHandle,
            XalanHandle     theXalanHandle);

    /**
     * Set a top-level stylesheet parameter.  This value can be evaluated via
     * xsl:param-variable.
     *
     * @param key               The name of the param
     * @param expression        The expression that will be evaluated
     * @param theXalanHandle    The handle of XalanTransformer instance.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(void)
    XalanSetStylesheetParam(
                const char*     key,
                const char*     expression,
                XalanHandle     theXalanHandle);

    /**
     * Set a top-level stylesheet parameter.  This value can be evaluated via
     * xsl:param-variable.  The key and expression parameters must be
     * encoded in UTF-16.
     *
     * @param key name of the param
     * @param expression expression that will be evaluated
     * @param theXalanHandle    handle of XalanTransformer instance.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(void)
    XalanSetStylesheetParamUTF(
                const XalanUTF16Char*   key,
                const XalanUTF16Char*   expression,
                XalanHandle             theXalanHandle);


    /**
     * Set a top-level stylesheet nodeset parameter.  This value can be
     * evaluated via xsl:param-variable.  The value is a parsed document.
     *
     * @param key name of the param
     * @param theNodeset a preparsed document
     * @param theXalanHandle  handle of the XalanTransformer instance.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(void)
    XalanSetStylesheetParamNodeset(
                const char*             key,
                XalanPSHandle           theNodeset,
                XalanHandle             theXalanHandle);

    /**
     * Set a top-level stylesheet nodeset parameter.  This value can be
     * evaluated via xsl:param-variable.  The value is a parsed document.
     * The key name is a UTF-16 string.
     *
     * @param key name of the param
     * @param theNodeset a preparsed document
     * @param theXalanHandle  handle of the XalanTransformer instance.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(void)
    XalanSetStylesheetParamUTFNodeset(
                const XalanUTF16Char*   key,
                XalanPSHandle           theNodeset,
                XalanHandle             theXalanHandle);
        
    /**
     * Set a top-level stylesheet number parameter.  This value can be
     * evaluated via xsl:param-variable.  The value is a parsed document.
     *
     * @param key name of the param
     * @param theNumber a double floating point number
     * @param theXalanHandle  handle of the XalanTransformer instance.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(void)
    XalanSetStylesheetParamNumber(
                const char*             key,
                double                  theNumber,
                XalanHandle             theXalanHandle);

    /**
     * Set a top-level stylesheet number parameter.  This value can be
     * evaluated via xsl:param-variable.  The value is a parsed document.
     * The key name is a UTF-16 string.
     *
     * @param key name of the param
     * @param theNumber a double floating point number
     * @param theXalanHandle  handle of the XalanTransformer instance.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(void)
    XalanSetStylesheetParamUTFNumber(
                const XalanUTF16Char*   key,
                double                  theNumber,
                XalanHandle             theXalanHandle);

    /**
     * Clear the top-level stylesheet parameters.  Top-level stylesheet
     * parameters are sticky.  When set, they can be used for multiple
     * transformations. Use the XalanClearStylesheetParams function
     * to clear or reset the top-level stylesheet parameters.
     *
     * @param theXalanHandle  handle of the XalanTransformer instance.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(void)
    XalanClearStylesheetParams(
                XalanHandle             theXalanHandle);

    /**
     * Returns the last error that occurred as a 
     * result of calling transform.
     *
     * The signature for following function is really:
     * const char*
     * XalanGetLastError(XalanHandle theXalanHandle) const;
     *
     * @return  error message const character pointer.
     */
    XALAN_TRANSFORMER_EXPORT_FUNCTION(XalanCCharPtr)
    XalanGetLastError(XalanHandle   theXalanHandle);

#if defined(__cplusplus)
}
#endif



#endif  // XALAN_CAPI_HEADER_GUARD_1357924680
