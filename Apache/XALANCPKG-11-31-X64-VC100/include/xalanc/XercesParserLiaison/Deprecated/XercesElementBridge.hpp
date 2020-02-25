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
#if !defined(XERCESELEMENTBRIDGE_HEADER_GUARD_1357924680)
#define XERCESELEMENTBRIDGE_HEADER_GUARD_1357924680



#include <xalanc/XercesParserLiaison/XercesParserLiaisonDefinitions.hpp>



#if XERCES_VERSION_MAJOR >= 2
#include <xercesc/dom/deprecated/DOM_Element.hpp>
#else
#include <xercesc/dom/DOM_Element.hpp>
#endif



#include <xalanc/XalanDOM/XalanElement.hpp>



#include <xalanc/PlatformSupport/DOMStringHelper.hpp>



#include <xalanc/XercesParserLiaison/Deprecated/XercesDOM_NodeHack.hpp>
#include <xalanc/XercesParserLiaison/Deprecated/XercesNamedNodeMapBridge.hpp>
#include <xalanc/XercesParserLiaison/Deprecated/XercesNodeListBridge.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class XercesBridgeNavigator;


/**
 * This class is deprecated.
 *
 * @deprecated This class is part of the deprecated Xerces DOM bridge.
 */
class XALAN_XERCESPARSERLIAISON_EXPORT XercesElementBridge : public XalanElement
{
public:

    typedef XERCES_CPP_NAMESPACE_QUALIFIER DOM_Element  DOM_ElementType;

    XercesElementBridge(
            const DOM_ElementType&          theXercesElement,
            const XercesBridgeNavigator&    theNavigator);

    virtual
    ~XercesElementBridge();


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
    virtual XercesElementBridge*
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
    setNodeValue(const XalanDOMString&      nodeValue);

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
    setPrefix(const XalanDOMString& prefix);

    virtual bool
    isIndexed() const;

    virtual IndexType
    getIndex() const;

    //@}

    // These interfaces are inherited from XalanElement...

    /**
     * The name of the element. 
     *
     * For example, in: &lt;elementExample 
     * id="demo"&gt;  ... &lt;/elementExample&gt; , <code>tagName</code> has 
     * the value <code>"elementExample"</code>. Note that this is 
     * case-preserving in XML, as are all of the operations of the DOM. 
     */
    virtual const XalanDOMString&
    getTagName() const;

    /**
     * Retrieves an attribute value by name.
     *
     * @param name The name of the attribute to retrieve.
     * @return The <code>DOM_Attr</code> value as a string, or the empty  string if 
     *   that attribute does not have a specified or default value.
     */
    virtual const XalanDOMString&
    getAttribute(const XalanDOMString&      name) const;

    /**
     * Retrieves an <code>DOM_Attr</code> node by name.
     *
     * @param name The name (<CODE>nodeName</CODE>) of the attribute to retrieve.
     * @return The <code>DOM_Attr</code> node with the specified name (<CODE>nodeName</CODE>) or 
     *   <code>null</code> if there is no such attribute.
     */
    virtual XalanAttr*
    getAttributeNode(const XalanDOMString&      name) const;

    /**
     * Returns a <code>NodeList</code> of all descendant elements with a given 
     * tag name, in the order in which they would be encountered in a preorder 
     * traversal of the <code>DOM_Element</code> tree.  Caller is
     * responsible for deleting the XalanNodeList instance.
     *
     * @param name The name of the tag to match on. The special value "*" 
     *   matches all tags.
     * @return A list of matching <code>DOM_Element</code> nodes.
     */
    virtual XalanNodeList*
    getElementsByTagName(const XalanDOMString&      name) const;

    //@}
     /** @name Set functions. */
     //@{

    /**
     * Adds a new attribute. 
     * 
     * If an attribute with that name is already present 
     * in the element, its value is changed to be that of the value parameter. 
     * This value is a simple string, it is not parsed as it is being set. So 
     * any markup (such as syntax to be recognized as an entity reference) is 
     * treated as literal text, and needs to be appropriately escaped by the 
     * implementation when it is written out. In order to assign an attribute 
     * value that contains entity references, the user must create an 
     * <code>DOM_Attr</code> node plus any <code>Text</code> and 
     * <code>EntityReference</code> nodes, build the appropriate subtree, and 
     * use <code>setAttributeNode</code> to assign it as the value of an 
     * attribute.
     * @param name The name of the attribute to create or alter.
     * @param value Value to set in string form.
     * @exception DOMException
     *   INVALID_CHARACTER_ERR: Raised if the specified name contains an 
     *   illegal character.
     *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     */
    virtual void
    setAttribute(
            const XalanDOMString&   name, 
            const XalanDOMString&   value);

    /**
     * Adds a new attribute. 
     * 
     * If an attribute with that name (<CODE>nodeName</CODE>) is already present 
     * in the element, it is replaced by the new one.
     * @param newAttr The <code>DOM_Attr</code> node to add to the attribute list.
     * @return If the <code>newAttr</code> attribute replaces an existing 
     *   attribute, the replaced
     *   <code>DOM_Attr</code> node is returned, otherwise <code>null</code> is 
     *   returned.
     * @exception DOMException
     *   WRONG_DOCUMENT_ERR: Raised if <code>newAttr</code> was created from a 
     *   different document than the one that created the element.
     *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     *   <br>INUSE_ATTRIBUTE_ERR: Raised if <code>newAttr</code> is already an 
     *   attribute of another <code>DOM_Element</code> object. The DOM user must 
     *   explicitly clone <code>DOM_Attr</code> nodes to re-use them in other 
     *   elements.
     */
    virtual XalanAttr*
    setAttributeNode(XalanAttr*     newAttr);

    //@}
    /** @name Functions which modify the Element. */
    //@{
    
    /**
     * Removes the specified attribute node.
     * If the removed <CODE>DOM_Attr</CODE>
     *   has a default value it is immediately replaced. The replacing attribute 
     *   has the same namespace URI and local name, as well as the original prefix, 
     *   when applicable.
     *
     * @param oldAttr The <code>DOM_Attr</code> node to remove from the attribute 
     *   list.
     * @return The <code>DOM_Attr</code> node that was removed.
     * @exception DOMException
     *   NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     *   <br>NOT_FOUND_ERR: Raised if <code>oldAttr</code> is not an attribute 
     *   of the element.
     */
    virtual XalanAttr*
    removeAttributeNode(XalanAttr*  oldAttr);

    /**
     * Removes an attribute by name. 
     *
     * If the removed attribute 
     *   is known to have a default value, an attribute immediately appears 
     *   containing the default value as well as the corresponding namespace URI, 
     *   local name, and prefix when applicable.<BR>To remove an attribute by local 
     *   name and namespace URI, use the <CODE>removeAttributeNS</CODE> method.
     * @param name The name of the attribute to remove.
     * @exception DOMException
     *   NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     */
    virtual void
    removeAttribute(const XalanDOMString&   name);

    //@}
    /** @name Functions introduced in DOM Level 2. */
    //@{

    /**
     * Retrieves an attribute value by local name and namespace URI.
     *
     * @param namespaceURI The <em>namespace URI</em> of
     *    the attribute to retrieve.
     * @param localName The <em>local name</em> of the
     *    attribute to retrieve.
     * @return The <code>DOM_Attr</code> value as a string, or an empty string if
    *    that attribute does not have a specified or default value.
     */
    virtual const XalanDOMString&
    getAttributeNS(
            const XalanDOMString&   namespaceURI,
            const XalanDOMString&   localName) const;

    /**
     * Adds a new attribute. If the given 
     *   <CODE>namespaceURI</CODE> is <CODE>null</CODE> or an empty string and the 
     *   <CODE>qualifiedName</CODE> has a prefix that is "xml", the new attribute 
     *   is bound to the predefined namespace 
     *   "http://www.w3.org/XML/1998/namespace". 
     *   If an attribute with the same local name and namespace URI is already 
     *   present on the element, its prefix is changed to be the prefix part of the 
     *   <CODE>qualifiedName</CODE>, and its value is changed to be the 
     *   <CODE>value</CODE> parameter. 
     * This value is a simple string, it is
     * not parsed as it is being set. So any markup (such as syntax to be
     * recognized as an entity reference) is treated as literal text, and
     * needs to be appropriately escaped by the implementation when it is
     * written out. In order to assign an attribute value that contains entity
     * references, the user must create a <code>DOM_Attr</code> node plus any
     * <code>DOM_Text</code> and <code>DOM_EntityReference</code> nodes, build the
     * appropriate subtree, and use <code>setAttributeNodeNS</code> or
     * <code>setAttributeNode</code> to assign it as the value of an
     * attribute.
     * @param namespaceURI The <em>namespace URI</em> of
     *    the attribute to create or alter.
     * @param localName The <em>local name</em> of the
     *    attribute to create or alter.
     * @param value The value to set in string form.
     * @exception DOMException
     *   INVALID_CHARACTER_ERR: Raised if the specified qualified name contains an 
     *   illegal character.
     *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     * <br>
     *   NAMESPACE_ERR: Raised if the <CODE>qualifiedName</CODE> is 
     *         malformed, if the <CODE>qualifiedName</CODE> has a prefix that is 
     *         "xml" and the <CODE>namespaceURI</CODE> is neither <CODE>null</CODE> 
     *         nor an empty string nor "http://www.w3.org/XML/1998/namespace", or 
     *         if the <CODE>qualifiedName</CODE> has a prefix that is "xmlns" but 
     *         the <CODE>namespaceURI</CODE> is neither <CODE>null</CODE> nor an 
     *         empty string, or if if the <CODE>qualifiedName</CODE> has a prefix 
     *         different from "xml" and "xmlns" and the <CODE>namespaceURI</CODE> 
     *         is <CODE>null</CODE> or an empty string.
     */
    virtual void
    setAttributeNS(
            const XalanDOMString&   namespaceURI,
            const XalanDOMString&   qualifiedName,
            const XalanDOMString&   value);

    /**
     * Removes an attribute by local name and namespace URI. If the
     * removed attribute has a default value it is immediately replaced.
     * The replacing attribute has the same namespace URI and local name, as well as 
     * the original prefix.<BR>HTML-only DOM implementations do not need to 
     * implement this method.
     *
     * @param namespaceURI The <em>namespace URI</em> of
     *    the attribute to remove.
     * @param localName The <em>local name</em> of the
     *    attribute to remove.
     * @exception DOMException
     *   NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
     */
    virtual void
    removeAttributeNS(
            const XalanDOMString&   namespaceURI,
            const XalanDOMString&   localName);

    /**
     * Retrieves an <code>DOM_Attr</code> node by local name and namespace URI.
     *
     * @param namespaceURI The <em>namespace URI</em> of
     *    the attribute to retrieve.
     * @param localName The <em>local name</em> of the
     *    attribute to retrieve.
     * @return The <code>DOM_Attr</code> node with the specified attribute local
     *    name and namespace URI or <code>null</code> if there is no such attribute.
     */
    virtual XalanAttr*
    getAttributeNodeNS(
            const XalanDOMString&   namespaceURI,
            const XalanDOMString&   localName) const;

    /**
      * Adds a new attribute. 
      * 
      * If an attribute with that local name and namespace URI is already present 
      * in the element, it is replaced by the new one.
      * @param newAttr The <code>DOM_Attr</code> node to add to the attribute list.
      * @return If the <code>newAttr</code> attribute replaces an existing
      *    attribute with the same <em>local name</em> and <em>namespace URI</em>,
      *    the replaced <code>DOM_Attr</code> node is
      *    returned, otherwise <code>null</code> is returned.
      * @exception DOMException
      *   WRONG_DOCUMENT_ERR: Raised if <code>newAttr</code> was created from a 
      *   different document than the one that created the element.
      *   <br>NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
      *   <br>INUSE_ATTRIBUTE_ERR: Raised if <code>newAttr</code> is already an 
      *   attribute of another <code>DOM_Element</code> object. The DOM user must 
      *   explicitly clone <code>DOM_Attr</code> nodes to re-use them in other 
      *   elements.
      */
    virtual XalanAttr*
    setAttributeNodeNS(XalanAttr*   newAttr);

    /**
     * Returns a <code>DOM_NodeList</code> of all the <code>DOM_Element</code>s
     * with a given local name and namespace URI in the order in which they
     * would be encountered in a preorder traversal of the
     * <code>DOM_Document</code> tree, starting from this node.  Caller is
     * responsible for deleting the XalanNodeList instance.
     *
     * @param namespaceURI The <em>namespace URI</em> of
     *    the elements to match on. The special value "*" matches all
     *    namespaces.
     * @param localName The <em>local name</em> of the
     *    elements to match on. The special value "*" matches all local names.
     * @return A new <code>DOM_NodeList</code> object containing all the matched
     *    <code>Element</code>s.
     */
    virtual XalanNodeList*
    getElementsByTagNameNS(
            const XalanDOMString&   namespaceURI,
            const XalanDOMString&   localName) const;

    /**
     * Get the Xerces node this instance represent.
     *
     * @return The Xerces node
     */
    DOM_ElementType
    getXercesNode() const
    {
        return m_xercesNode;
    }

    //@}

private:

    // Not implemented...
    XercesElementBridge(const XercesElementBridge&  theSource);

    XalanNode&
    operator=(const XalanNode&  theSource);

    bool
    operator==(const XercesElementBridge&   theRHS) const;

    // Data members...
    XercesDOM_ElementHack               m_xercesNode;

    const XercesBridgeNavigator&        m_navigator;

    XercesNodeListBridge                m_children;

    XercesNamedNodeMapBridge            m_attributes;
};



XALAN_CPP_NAMESPACE_END



#endif  // !defined(XERCESELEMENTBRIDGE_HEADER_GUARD_1357924680)
