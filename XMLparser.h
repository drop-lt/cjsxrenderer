#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <stdlib.h>
#include <stdint.h>

#define XML_ATTRIBUTE_NAME_SIZE 32
#define XML_ATTRIBUTE_NAME_VALUE 64

typedef struct XMLElement XMLElement;
typedef struct XMLAttribute XMLAttribute;


/**
 * @brief create a new XML Attribute struct
 * 
 * @param name: the attribute name
 * @param value: the attribute's value
 * 
 * @return XMLAttribute* to a heap-allocated element.
 *  
 */
XMLAttribute* XML_createAttributeWith(const char* name, const char* value);

/**
 * @brief create a new XML Element struct
 * 
 * @param name the element's tag name
 * @param attributes: an array of attribues
 * @param attribute_count: the count of elements inside of the array
 * @param children: an array of child elements
 * @param children_count: count of children, set to 1 if using as text
 * @param text_child: set to 1 when [children] points to a string
 * 
 * @return heap-allocated xml element
 * 
 */
XMLElement* XML_createElementWith(const char* name, XMLAttribute* attributes, size_t attribute_count, XMLElement* children, size_t children_count, uint8_t text_child);


/**
 * @brief create a string with the elements given by the struct
 * 
 * @param element: element to representate
 * 
 * @return a heap-allocated string with element contents
 */
const char* ElementToString(XMLElement* element);

#endif // !XML_PARSER_H


