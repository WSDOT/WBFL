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
#if !defined(XERCESTEXTBRIDGE_HEADER_GUARD_1357924680)
#define XERCESTEXTBRIDGE_HEADER_GUARD_1357924680



#include <xalanc/XercesParserLiaison/XercesParserLiaisonDefinitions.hpp>



#if XERCES_VERSION_MAJOR >= 2
#include <xercesc/dom/deprecated/DOM_Text.hpp>
#else
#include <xercesc/dom/DOM_Text.hpp>
#endif


#include <xalanc/XalanDOM/XalanText.hpp>



#include <xalanc/XercesParserLiaison/Deprecated/XercesDOM_NodeHack.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class XercesBridgeNavigator;


/**
 * This class is deprecated.
 *
 * @deprecated This class is part of the deprecated Xerces DOM bridge.
 */
class XALAN_XERCESPARSERLIAISON_EXPORT XercesTextBridge : public XalanText
{
public:

    typedef XERCES_CPP_NAMESPACE_QUALIFIER DOM_Text     DOM_TextType;

    XercesTextBridge(
            const DOM_TextType&             theXercesText,
            const XercesBridgeNavigator&    theNavigator);

    virtual
    ~XercesTextBridge();


    /**
     * Gets the name of this node.
     */
    virtual const XalanDOMString&
    getNodeName() const;

    /**
     * Gets the value of this node, depending on its type.
     */
    virtual const XalanDOMString&
    getNodeValue() const;

    /**
     * An enum value representing the type of the underlying object.
     */
    virtual NodeType
    getNodeType() const;

    /**
     * Gets the parent of this node.
     *
     * All nodes, except <code>Document</code>,
     * <code>DocumentFragment</code>, and <code>Attr</code> may have a parent.
     * However, if a node has just been created and not yet added to the tree,
     * or if it has been removed from the tree, a <code>null</code> DOM_Node
     * is returned.
     */
    virtual XalanNode*
    getParentNode() const;

    /**
     * Gets a <code>NodeList</code> that contains all children of this node.
     *
     * If there
     * are no children, this is a <code>NodeList</code> containing no nodes.
     * The content of the returned <code>NodeList</code> is "live" in the sense
     * that, for instance, changes to the children of the node object that
     * it was created from are immediately reflected in the nodes returned by
     * the <code>NodeList</code> accessors; it is not a static snapshot of the
     * content of the node. This is true for every <code>NodeList</code>,
     * including the ones returned by the <code>getElementsByTagName</code>
     * method.
     */
    virtual const XalanNodeList*
    getChildNodes() const;

    /**
     * Gets the first child of this node.
     *
     * If there is no such node, this returns <code>null</code>.
     */
    virtual XalanNode*
    getFirstChild() const;

    /**
     * Gets the last child of this node.
     *
     * If there is no such node, this returns <code>null</code>.
     */
    virtual XalanNode*
    getLastChild() const;

    /**
     * Gets the node immediately preceding this node.
     *
     * If there is no such node, this returns <code>null</code>.
     */
    virtual XalanNode*
    getPreviousSibling() const;

    /**
     * Gets the node immediately following this node.
     *
     * If there is no such node, this returns <code>null</code>.
     */
    virtual XalanNode*
    getNextSibling() const;

    /**
     * Gets a <code>NamedNodeMap</code> containing the attributes of this node (if it
     * is an <code>Element</code>) or <code>null</code> otherwise.
     */
    virtual const XalanNamedNodeMap*
    getAttributes() const;

    /**
     * Gets the <code>DOM_Document</code> object associated with this node.
     *
     * This is also
     * the <code>DOM_Document</code> object used to create new nodes. When this
     * node is a <code>DOM_Document</code> or a <code>DOM_DocumentType</code>
     * which is not used with any <code>DOM_Document</code> yet, this is
     * <code>null</code>.
     */
    virtual XalanDocument*
    getOwnerDocument() const;

    //@}
    /** @name Cloning function. */
    //@{

    /**
     * Returns a duplicate of this node.
     *
     * This function serves as a generic copy constructor for nodes.
     *
     * The duplicate node has no parent (
     * <code>parentNode</code> returns <code>null</code>.).
     * <br>Cloning an <code>Element</code> copies all attributes and their
     * values, including those generated by the  XML processor to represent
     * defaulted attributes, but this method does not copy any text it contains
     * unless it is a deep clone, since the text is contained in a child
     * <code>Text</code> node. Cloning any other type of node simply returns a
     * copy of this node.
     * @param deep If <code>true</code>, recursively clone the subtree under the
     *   specified node; if <code>false</code>, clone only the node itself (and
     *   its attributes, if it is an <code>Element</code>).
     * @return The duplicate node.
     */
#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
    virtual XalanNode*
#else
    virtual XercesTextBridge*
#endif
    cloneNode(bool deep) const;

    //@}
    /** @name Functions to modify the DOM Node. */
    //@{

    /**
     * Inserts the node <code>newChild</code> before the existing child node
     * <code>refChild</code>.
     *
     * If <code>refChild</code> is <code>null</code>,
     * insert <code>newChild</code> at the end of the list of children.
     * <br>If <code>newChild</code> is a <code>DocumentFragment</code> object,
     * all of its children are inserted, in the same order, before
     * <code>refChild</code>. If the <code>newChild</code> is already in the
     * tree, it is first removed.  Note that a <code>DOM_Node</code> that
     * has never been assigned to refer to an actual node is == null.
     * @param newChild The node to insert.
     * @param refChild The reference node, i.e., the node before which the new
     *   node must be inserted.
     * @return The node being inserted.
     */
    virtual XalanNode*
    insertBefore(
            XalanNode*  newChild,
            XalanNode*  refChild);

    /**
     * Replaces the child node <code>oldChild</code> with <code>newChild</code>
     * in the list of children, and returns the <code>oldChild</code> node.
     *
     * If <CODE>newChild</CODE> is a <CODE>DOM_DocumentFragment</CODE> object,
     * <CODE>oldChild</CODE> is replaced by all of the <CODE>DOM_DocumentFragment</CODE>
     * children, which are inserted in the same order.
     *
     * If the <code>newChild</code> is already in the tree, it is first removed.
     * @param newChild The new node to put in the child list.
     * @param oldChild The node being replaced in the list.
     * @return The node replaced.
     */
    virtual XalanNode*
    replaceChild(
            XalanNode*  newChild,
            XalanNode*  oldChild);

    /**
     * Removes the child node indicated by <code>oldChild</code> from the list
     * of children, and returns it.
     *
     * @param oldChild The node being removed.
     * @return The node removed.
     */
    virtual XalanNode*
    removeChild(XalanNode*  oldChild);

    /**
     * Adds the node <code>newChild</code> to the end of the list of children of
     * this node.
     *
     * If the <code>newChild</code> is already in the tree, it is
     * first removed.
     * @param newChild The node to add.If it is a  <code>DocumentFragment</code>
     *   object, the entire contents of the document fragment are moved into
     *   the child list of this node
     * @return The node added.
     */
    virtual XalanNode*
    appendChild(XalanNode*  newChild);

    //@}
    /** @name Query functions. */
    //@{

    /**
     *  This is a convenience method to allow easy determination of whether a
     * node has any children.
     *
     * @return  <code>true</code> if the node has any children,
     *   <code>false</code> if the node has no children.
     */
    virtual bool
    hasChildNodes() const;


    //@}
    /** @name Set functions. */
    //@{


    /**
    * Sets the value of the node.
    *
    * Any node which can have a nodeValue (@see getNodeValue) will
    * also accept requests to set it to a string. The exact response to
    * this varies from node to node -- Attribute, for example, stores
    * its values in its children and has to replace them with a new Text
    * holding the replacement value.
    *
    * For most types of Node, value is null and attempting to set it
    * will throw DOMException(NO_MODIFICATION_ALLOWED_ERR). This will
    * also be thrown if the node is read-only.
    */
    virtual void
    setNodeValue(const XalanDOMString&  nodeValue);

    //@}
    /** @name Functions introduced in DOM Level 2. */
    //@{

    /**
     * Puts all <CODE>DOM_Text</CODE>
     * nodes in the full depth of the sub-tree underneath this <CODE>DOM_Node</CODE>, 
     * including attribute nodes, into a "normal" form where only markup (e.g., 
     * tags, comments, processing instructions, CDATA sections, and entity 
     * references) separates <CODE>DOM_Text</CODE>
     * nodes, i.e., there are no adjacent <CODE>DOM_Text</CODE>
     * nodes. This can be used to ensure that the DOM view of a document is the 
     * same as if it were saved and re-loaded, and is useful when operations 
     * (such as XPointer lookups) that depend on a particular document tree 
     * structure are to be used.
     * <P><B>Note:</B> In cases where the document contains <CODE>DOM_CDATASections</CODE>, 
     * the normalize operation alone may not be sufficient, since XPointers do 
     * not differentiate between <CODE>DOM_Text</CODE>
     * nodes and <CODE>DOM_CDATASection</CODE> nodes.</P>
     */
    virtual void
    normalize();

    /**
     * Tests whether the DOM implementation implements a specific
     * feature and that feature is supported by this node.
     * @param feature The string of the feature to test. This is the same
     * name as what can be passed to the method <code>hasFeature</code> on
     * <code>DOMImplementation</code>.
     * @param version This is the version number of the feature to test. In
     * Level 2, version 1, this is the string "2.0". If the version is not
     * specified, supporting any version of the feature will cause the
     * method to return <code>true</code>.
     * @return Returns <code>true</code> if the specified feature is supported
     * on this node, <code>false</code> otherwise.
     */
    virtual bool
    isSupported(
            const XalanDOMString&   feature,
            const XalanDOMString&   version) const;

    /**
     * Get the <em>namespace URI</em> of
     * this node, or <code>null</code> if it is unspecified.
     * <p>
     * This is not a computed value that is the result of a namespace lookup
     * based on an examination of the namespace declarations in scope. It is
     * merely the namespace URI given at creation time.
     * <p>
     * For nodes of any type other than <CODE>ELEMENT_NODE</CODE> and 
     * <CODE>ATTRIBUTE_NODE</CODE> and nodes created with a DOM Level 1 method, 
     * such as <CODE>createElement</CODE> from the <CODE>Document</CODE>
     * interface, this is always <CODE>null</CODE>.
     */
    virtual const XalanDOMString&
    getNamespaceURI() const;

    /**
     * Get the <em>namespace prefix</em>
     * of this node, or <code>null</code> if it is unspecified.
     */
    virtual const XalanDOMString&
    getPrefix() const;

    /**
     * Returns the local part of the <em>qualified name</em> of this node.
     * <p>
     * For nodes created with a DOM Level 1 method, such as
     * <code>createElement</code> from the <code>DOM_Document</code> interface,
     * it is null.
     */
    virtual const XalanDOMString&
    getLocalName() const;

    /**
     * Set the <em>namespace prefix</em> of this node.
     * <p>
     * Note that setting this attribute, when permitted, changes 
     * the <CODE>nodeName</CODE> attribute, which holds the <EM>qualified 
     * name</EM>, as well as the <CODE>tagName</CODE> and <CODE>name</CODE> 
     * attributes of the <CODE>DOM_Element</CODE> and <CODE>DOM_Attr</CODE>
     * interfaces, when applicable.
     * <p>
     * Note also that changing the prefix of an 
     * attribute, that is known to have a default value, does not make a new 
     * attribute with the default value and the original prefix appear, since the 
     * <CODE>namespaceURI</CODE> and <CODE>localName</CODE> do not change.
     *
     * @param prefix The prefix of this node.
     * @exception DOMException
     *   INVALID_CHARACTER_ERR: Raised if the specified prefix contains
     *                          an illegal character.
     * <br>
     *   NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     * <br>
     *   NAMESPACE_ERR: Raised if the specified <CODE>prefix</CODE> is 
     *       malformed, if the specified prefix is "xml" and the 
     *       <CODE>namespaceURI</CODE> of this node is different from 
     *       "http://www.w3.org/XML/1998/namespace", if specified prefix is 
     *       "xmlns" and the <CODE>namespaceURI</CODE> is neither 
     *       <CODE>null</CODE> nor an empty string, or if the 
     *       <CODE>localName</CODE> is <CODE>null</CODE>.
     */
    virtual void
    setPrefix(const XalanDOMString&     prefix);

    virtual bool
    isIndexed() const;

    virtual IndexType
    getIndex() const;

    //@}

    // These interfaces are inherited from XalanText...

    /** @name Getter functions. */
    //@{
    /**
     * Returns the character data of the node that implements this interface. 
     *
     * The DOM implementation may not put arbitrary limits on the amount of data that 
     * may be stored in a  <code>CharacterData</code> node. However, 
     * implementation limits may  mean that the entirety of a node's data may 
     * not fit into a single <code>DOMString</code>. In such cases, the user 
     * may call <code>substringData</code> to retrieve the data in 
     * appropriately sized pieces.
     * @exception DOMException
     *   NO_MODIFICATION_ALLOWED_ERR: Raised when the node is readonly.
     * @exception DOMException
     *   DOMSTRING_SIZE_ERR: Raised when it would return more characters than 
     *   fit in a <code>DOMString</code> variable on the implementation 
     *   platform.
     */
    virtual const XalanDOMString&
    getData() const;

    /**
     * Returns the number of characters that are available through <code>data</code> and 
     * the <code>substringData</code> method below. 
     *
     * This may have the value 
     * zero, i.e., <code>CharacterData</code> nodes may be empty.
     */
    virtual unsigned int
    getLength() const;

    /**
     * Extracts a range of data from the node.
     *
     * @param offset Start offset of substring to extract.
     * @param count The number of characters to extract.
     * @return The specified substring. If the sum of <code>offset</code> and 
     *   <code>count</code> exceeds the <code>length</code>, then all 
     *   characters to the end of the data are returned.
     * @exception DOMException
     *   INDEX_SIZE_ERR: Raised if the specified offset is negative or greater 
     *   than the number of characters in <code>data</code>, or if the 
     *   specified <code>count</code> is negative.
     *   <br>DOMSTRING_SIZE_ERR: Raised if the specified range of text does not 
     *   fit into a <code>DOMString</code>.
     */
    virtual XalanDOMString
    substringData(
            unsigned int    offset, 
            unsigned int    count) const;

    //@}
    /** @name Functions that set or change data. */
    //@{
    /**
     * Append the string to the end of the character data of the node.
     *
     * Upon success, <code>data</code> provides access to the concatenation of 
     * <code>data</code> and the <code>DOMString</code> specified.
     * @param arg The <code>DOMString</code> to append.
     * @exception DOMException
     *   NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     */
    virtual void
    appendData(const XalanDOMString&    arg);

    /**
     * Insert a string at the specified character offset.
     *
     * @param offset The character offset at which to insert.
     * @param arg The <code>DOMString</code> to insert.
     * @exception DOMException
     *   INDEX_SIZE_ERR: Raised if the specified offset is negative or greater 
     *   than the number of characters in <code>data</code>.
     *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     */
    virtual void
    insertData(
            unsigned int            offset,
            const XalanDOMString&   arg);

    /**
     * Remove a range of characters from the node. 
     *
     * Upon success, 
     * <code>data</code> and <code>length</code> reflect the change.
     * @param offset The offset from which to remove characters.
     * @param count The number of characters to delete. If the sum of 
     *   <code>offset</code> and <code>count</code> exceeds <code>length</code> 
     *   then all characters from <code>offset</code> to the end of the data 
     *   are deleted.
     * @exception DOMException
     *   INDEX_SIZE_ERR: Raised if the specified offset is negative or greater 
     *   than the number of characters in <code>data</code>, or if the 
     *   specified <code>count</code> is negative.
     *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     */
    virtual void
    deleteData(
            unsigned int    offset, 
            unsigned int    count);

    /**
     * Replace the characters starting at the specified character offset with 
     * the specified string.
     *
     * @param offset The offset from which to start replacing.
     * @param count The number of characters to replace. If the sum of 
     *   <code>offset</code> and <code>count</code> exceeds <code>length</code>
     *   , then all characters to the end of the data are replaced (i.e., the 
     *   effect is the same as a <code>remove</code> method call with the same 
     *   range, followed by an <code>append</code> method invocation).
     * @param arg The <code>DOMString</code> with which the range must be 
     *   replaced.
     * @exception DOMException
     *   INDEX_SIZE_ERR: Raised if the specified offset is negative or greater 
     *   than the number of characters in <code>data</code>, or if the 
     *   specified <code>count</code> is negative.
     *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     */
    virtual void
    replaceData(
            unsigned int            offset, 
            unsigned int            count, 
            const XalanDOMString&   arg);

  //@}

    //@}
    /** @name Functions to modify the Text node. */
    //@{

    /**
     * Breaks this node into two nodes at the specified 
     * offset, keeping both in the tree as siblings. 
     *
     * This node then only 
     * contains all the content up to the <code>offset</code> point. And a new 
     * node of the same nodeType, which is inserted as the next sibling of this 
     * node, contains all the content at and after the <code>offset</code> 
     * point. When the <code>offset</code> is equal to the lenght of this node,
     * the new node has no data.
     * @param offset The offset at which to split, starting from 0.
     * @return The new <code>Text</code> node.
     * @exception DOMException
     *   INDEX_SIZE_ERR: Raised if the specified offset is negative or greater 
     *   than the number of characters in <code>data</code>.
     *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     */
    virtual XalanText*
    splitText(unsigned int  offset);

    //@}

    virtual bool
    isWhitespace() const;

    /**
     * Get the Xerces node this instance represent.
     *
     * @return The Xerces node
     */
    DOM_TextType
    getXercesNode() const
    {
        return m_xercesNode;
    }

private:

    // Not implemented...
    XercesTextBridge(const XercesTextBridge&    theSource);

    XercesTextBridge&
    operator=(const XercesTextBridge&   theSource);

    bool
    operator==(const XercesTextBridge&  theRHS) const;

    // Data members...
    XercesDOM_TextHack              m_xercesNode;

    const XercesBridgeNavigator&    m_navigator;
};



XALAN_CPP_NAMESPACE_END



#endif  // !defined(XERCESTEXTBRIDGE_HEADER_GUARD_1357924680)
