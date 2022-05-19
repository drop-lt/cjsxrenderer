#include "XMLparser.h"

struct XMLElement {
	const char* name;
	XMLAttribute* attributes;
	size_t attribute_size;
	union {
		XMLElement* children;
		const char* text;
	};
	size_t children_count; //! 0 for none, 1 for text / one child and 2 for more than one child (no text)
	uint8_t isChildText;
};