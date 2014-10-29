/**************************************************************************************************
// file:	Engine\Physics\CGrid.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the quad tree class
 **************************************************************************************************/
#ifndef A2DE_CGRID_H
#define A2DE_CGRID_H

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

#include "../a2de_vals.h"
#include "../a2de_graphics.h"
#include "../a2de_math.h"

A2DE_BEGIN

class a2de::Shape;
class a2de::Color;

template<typename T>
class Grid {

public:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="bounds">The bounds.</param>
     **************************************************************************************************/
    Grid(const a2de::Rectangle& bounds);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     **************************************************************************************************/
    ~Grid();

    /**************************************************************************************************
     * <summary>Adds an element to the tree.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="elem">The const T& to add.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool Add(const T& elem);

    /**************************************************************************************************
     * <summary>Adds an element to the tree.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="elem">The const T* to add.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool Add(const T* elem);

    /**************************************************************************************************
     * <summary>Removes the given element.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="elem">The const T& to remove.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool Remove(const T& elem);

    /**************************************************************************************************
     * <summary>Removes the given element.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="elem">The const T* to remove.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool Remove(const T* elem);

    /**************************************************************************************************
     * <summary>Updates the given element.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="elem">The element.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool Update(const T& elem);

    /**************************************************************************************************
     * <summary>Updates the given element.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="elem">The element.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool Update(const T* elem);

    /**************************************************************************************************
     * <summary>Adds a range of elements.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="elems">[in,out] The std::vector<T>& to add.</param>
     **************************************************************************************************/
    void Add(std::vector<T>& elems);

    /**************************************************************************************************
     * <summary>Removes the given elements.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="elems">[in,out] The std::vector<T>& to remove.</param>
     **************************************************************************************************/
    void Remove(std::vector<T>& elems);

    /**************************************************************************************************
     * <summary>Updates the given elements.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="elems">[in,out] The elems.</param>
     **************************************************************************************************/
    void Update(std::vector<T>& elems);

    /**************************************************************************************************
     * <summary>Clears this object to its blank/initial state.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     **************************************************************************************************/
    void Clear();

    /**************************************************************************************************
     * <summary>Clears the node to its blank/initial state.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="node">[in,out] If non-null, the node.</param>
     **************************************************************************************************/
    void Clear(Grid<T>* node);

    /**************************************************************************************************
     * <summary>Gets the node bounds.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <returns>The bounds.</returns>
     **************************************************************************************************/
    const a2de::Rectangle& GetBounds() const;

    /**************************************************************************************************
     * <summary>Gets the bounds.</summary>
     * <remarks>Casey Ugone, 8/22/2013.</remarks>
     * <returns>The bounds.</returns>
     **************************************************************************************************/
    a2de::Rectangle& GetBounds();

    /**************************************************************************************************
     * <summary>Gets the tree height.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <returns>.</returns>
     **************************************************************************************************/
    unsigned long Height();

    /**************************************************************************************************
     * <summary>Gets the tree divisions.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <returns>.</returns>
     **************************************************************************************************/
    unsigned long Divisions();

    /**************************************************************************************************
     * <summary>Gets the number of elements in tree.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <returns>The total number of elements in tree.</returns>
     **************************************************************************************************/
    unsigned long NumberOfElementsInTree();

    /**************************************************************************************************
     * <summary>Queries a given area.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="area">The area.</param>
     * <returns>.</returns>
     **************************************************************************************************/
    std::vector<T> Query(const a2de::Shape& area);

    /**************************************************************************************************
     * <summary>Gets the nodes by element.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="elem">[in,out] The element.</param>
     * <returns>null if it fails, else the nodes by element.</returns>
     **************************************************************************************************/
    std::vector<Grid<T>*> GetNodesByElement(T& elem);

    /**************************************************************************************************
     * <summary>Gets the nodes by location.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="loc">[in,out] The location.</param>
     * <returns>null if it fails, else the nodes by location.</returns>
     **************************************************************************************************/
    std::vector<Grid<T>*> GetNodesByLocation(a2de::Vector2D& loc);

    /**************************************************************************************************
     * <summary>Gets the sibling nodes.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="node">[in,out] If non-null, the node.</param>
     * <returns>null if it fails, else the siblings.</returns>
     **************************************************************************************************/
    std::vector<Grid<T>*> GetSiblings(Grid<T>* node);

    /**************************************************************************************************
     * <summary>Gets all elements.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <returns>all elements.</returns>
     **************************************************************************************************/
    std::vector<T> GetAllElements();

    /**************************************************************************************************
     * <summary>Draws the tree.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="dest">         [in,out] If non-null, destination for the.</param>
     * <param name="top_to_bottom">true to top to bottom.</param>
     **************************************************************************************************/
    void Draw(BITMAP* dest, bool top_to_bottom);

    /**************************************************************************************************
     * <summary>Gets the maximum elements per node.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <returns>The maximum elements per node.</returns>
     **************************************************************************************************/
    static unsigned long GetMaxElementsPerNode();

    /**************************************************************************************************
     * <summary>Sets the maximum elements per node.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="max_elements">The maximum elements.</param>
     **************************************************************************************************/
    static void SetMaxElementsPerNode(unsigned long max_elements);

    /**************************************************************************************************
     * <summary>Sets the node color.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="color">The color.</param>
     **************************************************************************************************/
    void SetNodeColor(const a2de::Color& color);

    /**************************************************************************************************
     * <summary>Gets the node color.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <returns>The node color.</returns>
     **************************************************************************************************/
    const a2de::Color& GetNodeColor();
    
    void ResetNodeColor();

protected:
private:

    /// <summary> The default node color </summary>
    a2de::Color DEFAULT_NODE_COLOR;
    
    /**************************************************************************************************
     * <summary>Queries a node.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="node">             [in,out] If non-null, the node.</param>
     * <param name="area">             The area.</param>
     * <param name="selected_elements">[in,out] The selected elements.</param>
     **************************************************************************************************/
    void QueryNode(Grid<T>* node, const a2de::Shape& area, std::vector<T>& selected_elements);

    /**************************************************************************************************
     * <summary>Removes the element described by elem.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="elem">The element.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool RemoveElement(const T& elem);

    /**************************************************************************************************
     * <summary>Gets the elements.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="node">[in,out] If non-null, the node.</param>
     * <returns>The elements.</returns>
     **************************************************************************************************/
    std::vector<T> GetElements(Grid<T>* node);
    
    /// <summary> The elements </summary>
    std::vector<T> _elements;
    /// <summary> The bounds </summary>
    a2de::Rectangle _bounds;

    /// <summary> The grid of rectangles </summary>
    std::vector<a2de::Rectangle> _grid;

    /// <summary> The dimensions of each cell </summary>
    a2de::Vector2D _cell_dimensions;

    //DO NOT COPY!

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="other">The other.</param>
     **************************************************************************************************/
    Grid(const Grid<T>& other);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    Grid<T>& operator=(const Grid<T>& rhs);

};


template<typename T>
T* ptr(T& obj) {
    //turn reference into pointer!
    return &obj;
}

template<typename T>
T* ptr(T* obj) {
    //obj is already pointer, return it!
    return obj;
}

template<typename T>
unsigned long Grid<T>::MAX_ELEMENTS = 2;

template<typename T>
std::size_t Grid<T>::MAX_CHILDREN = 4;


template<typename T>
Grid<T>::Grid(const a2de::Rectangle& bounds) : _elements(), _bounds(bounds), _parent(nullptr), _children(4) {
    DEFAULT_NODE_COLOR = a2de::Color::WHITE();
    _bounds.SetColor(_bounds.GetColor());
    _bounds.SetFill(false);
}

template<typename T>
Grid<T>::Grid(Grid<T>* parent_node, const a2de::Rectangle& bounds) : _elements(), _bounds(bounds), _parent(parent_node), _children(4) {
    DEFAULT_NODE_COLOR = a2de::Color::WHITE();
    _bounds.SetColor(_bounds.GetColor());
    _bounds.SetFill(false);
}

template<typename T>
Grid<T>::Grid(Grid<T>* parent_node, const a2de::Rectangle& bounds, std::vector<T>& elems) : _elements(elems), _bounds(bounds), _parent(parent_node), _children(4) {
    DEFAULT_NODE_COLOR = a2de::Color::WHITE();
    _bounds.SetColor(_bounds.GetColor());
    _bounds.SetFill(false);
    Add(elems);
}

template<typename T>
Grid<T>::~Grid() {
    this->_elements.clear();
    this->_parent = nullptr;
    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        delete this->_children[i];
        this->_children[i] = nullptr;
    }
}


template<typename T>
const a2de::Rectangle& Grid<T>::GetBounds() const {
    return _bounds;
}

template<typename T>
a2de::Rectangle& Grid<T>::GetBounds() {
    return const_cast<a2de::Rectangle&>(static_cast<const Grid<T>&>(*this).GetBounds());
}

template<typename T>
std::vector<Grid<T>*> Grid<T>::GetNodesByElement(T& elem) {

    std::vector<Grid<T>*> result;
    if(IsLeaf(this) == false) {
        for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
            std::vector<Grid<T>*> child_result = _children[i]->GetNodesByElement(elem);
        }
    } else {
        std::vector<T>::iterator _iter;
        if((_iter = std::find(_elements.begin(), _elements.end(), elem)) != _elements.end()) {
            result.push_back(this);
        }
    }
    return result;
}

template<typename T>
void Grid<T>::Remove(std::vector<T>& elems) {
    std::vector<T>::iterator b = elems.begin();
    std::vector<T>::iterator e = elems.end();
    for(std::vector<T>::iterator _iter = b; _iter != e; ++_iter) {
        this->Remove(*_iter);
    }
}

template<typename T>
std::vector<Grid<T>*> Grid<T>::GetNodesByLocation(a2de::Vector2D& loc) {
    std::vector<Grid<T>*> results;
    if(_bounds.Intersects(loc)) {
        if(IsLeaf(this) == false) {
            std::vector<Grid<T>*> child_results;
            for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
                child_results = _children[i]->GetNodesByLocation(loc);
                std::vector<Grid<T>*>::iterator b = child_results.begin();
                std::vector<Grid<T>*>::iterator e = child_results.end();
                for(std::vector<Grid<T>*>::iterator _iter = b; _iter != e; ++_iter) {
                    results.push_back(*_iter);
                }
                child_results.clear();
            }
        } else {
            results.push_back(this);
        }
    }
    return results;
}

template<typename T>
void Grid<T>::Add(std::vector<T>& elems) {
    std::vector<T>::iterator b = elems.begin();
    std::vector<T>::iterator e = elems.end();
    for(std::vector<T>::iterator _iter = b; _iter != e; ++_iter) {
        this->Add(*_iter);
    }
}

template<typename T>
std::vector<Grid<T>*> Grid<T>::GetSiblings(Grid<T>* node) {
    std::vector<Grid<T>*> siblings;
    if(node == nullptr) return siblings;
    if(node->_parent == nullptr) {
        siblings.push_back(node);
        return siblings;
    }
    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        siblings.push_back(_parent->_children[i]);
    }
    return siblings;

}

template<typename T>
std::vector<T> Grid<T>::GetAllElements() {
    return this->GetElements(this);
}

template<typename T>
std::vector<T> Grid<T>::GetElements(Grid<T>* node) {
    class IsInTotal {
    public:
        IsInTotal(std::vector<T>* total_elements) : _total_elements(total_elements) { }
        bool operator()(T& elem) {
            return std::find(_total_elements->begin(), _total_elements->end(), elem) == _total_elements->end();
        }
    private:
        std::vector<T>* _total_elements;
    };
    std::vector<T> total_elements;
    if(node == nullptr) return total_elements;
    if(IsLeaf(node)) return node->_elements;
    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        std::vector<T> c_elems(node->GetElements(node->_children[i]));
        std::size_t c_s = c_elems.size();
        for(std::size_t c = 0; c < c_s; ++c) {
            std::copy_if(c_elems.begin(), c_elems.end(), std::back_inserter(total_elements), IsInTotal(&total_elements));
        }
    }
    return total_elements;
}
template<typename T>
void Grid<T>::QueryNode(Grid<T>* node, const a2de::Shape& area, std::vector<T>& selected_elements) {

    if(node == nullptr) return;

    if(node->_bounds.Intersects(area) == false) return;

    if(IsLeaf(node)) {
        std::vector<T>::iterator b = node->_elements.begin();
        std::vector<T>::iterator e = node->_elements.end();
        for(std::vector<T>::iterator _iter = b; _iter != e; ++_iter) {
            selected_elements.push_back(*_iter);
        }
        return;
    }
    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        QueryNode(node->_children[i], area, selected_elements);
    }
}

template<typename T>
std::vector<T> Grid<T>::Query(const a2de::Shape& area) {
    std::vector<T> selected_elements;
    QueryNode(this, area, selected_elements);
    return selected_elements;
}

template<typename T>
unsigned long Grid<T>::GetMaxElementsPerNode() {
    return MAX_ELEMENTS;
}

template<typename T>
void Grid<T>::SetMaxElementsPerNode(unsigned long max_elements) {
    MAX_ELEMENTS = max_elements;
}

template<typename T>
const a2de::Color& Grid<T>::GetNodeColor() {
    return _bounds.GetColor();
}

template<typename T>
void Grid<T>::SetNodeColor(const a2de::Color& color) {
    _bounds.SetColor(color);
}

template<typename T>
void Grid<T>::ResetNodeColor() {
    _bounds.SetColor(DEFAULT_NODE_COLOR);
}

template<typename T>
unsigned long Grid<T>::NumberOfElementsInTree() {
    if(IsLeaf(this)) return _elements.size();
    unsigned long num_elements = 0;
    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        num_elements += _children[i]->NumberOfElementsInTree();
    }
    return num_elements;
}

template<typename T>
unsigned long Grid<T>::Divisions() {
    if(IsLeaf(this)) return 0;
    unsigned long num_divisions = MAX_CHILDREN;
    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        num_divisions += _children[i]->Divisions();
    }
    return num_divisions;
}

template<typename T>
unsigned long Grid<T>::Height() {

    if(IsLeaf(this)) return 0;
    unsigned long height = 1;
    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        height += _children[i]->Height();
    }
    return height;
}

template<typename T>
bool Grid<T>::IsLeaf(Grid<T>* node) {
    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        if(node->_children[i] == nullptr) continue;
        return false;
    }
    return true;
}

template<typename T>
void Grid<T>::DrawTopToBottom(BITMAP* dest) {
    _bounds.Draw(dest, _bounds.GetColor(), _bounds.IsFilled());
    if(IsLeaf(this) == false) {
        for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
            _children[i]->DrawTopToBottom(dest);
        }
    }
}

template<typename T>
void Grid<T>::DrawBottomToTop(BITMAP* dest) {
    if(IsLeaf(this) == false) {
        for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
            _children[i]->DrawBottomToTop(dest);
        }
    }
    _bounds.Draw(dest, _bounds.GetColor(), _bounds.IsFilled());
}

template<typename T>
void Grid<T>::Draw(BITMAP* dest, bool top_to_bottom) {
    top_to_bottom ? DrawTopToBottom(dest) : DrawBottomToTop(dest);
}

template<typename T>
void Grid<T>::SubDivide() {
    try {
        //Define 
        double half_width = _bounds.GetWidth();
        double half_height = _bounds.GetHeight();
        if(a2de::Math::ToScreenScale(half_width) <= 1.0 || a2de::Math::ToScreenScale(half_height) <= 1.0) return;

        a2de::Vector2D dimensions(half_width, half_height);
        a2de::Vector2D ul_pos(this->_bounds.GetPosition() - (a2de::Vector2D(half_width, half_height) / 2.0));
        a2de::Vector2D ur_pos(ul_pos + a2de::Vector2D(half_width, 0.0));
        a2de::Vector2D ll_pos(ul_pos + a2de::Vector2D(0.0, half_height));
        a2de::Vector2D lr_pos(ul_pos + a2de::Vector2D(half_width, half_height));
        a2de::Color color = _bounds.GetColor();
        bool filled = _bounds.IsFilled();

        a2de::Rectangle ul(ul_pos, dimensions, color, filled);
        a2de::Rectangle ur(ur_pos, dimensions, color, filled);
        a2de::Rectangle ll(ll_pos, dimensions, color, filled);
        a2de::Rectangle lr(lr_pos, dimensions, color, filled);

        _children[CHILD_UPPER_LEFT] = new Grid(this, ul);
        _children[CHILD_UPPER_RIGHT] = new Grid(this, ur);
        _children[CHILD_LOWER_LEFT] = new Grid(this, ll);
        _children[CHILD_LOWER_RIGHT] = new Grid(this, lr);

        //Give elements of mine to children, may or may not accept them.
        for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
            std::vector<T>::iterator b = _elements.begin();
            std::vector<T>::iterator e = _elements.end();
            for(std::vector<T>::iterator _iter = b; _iter != e; /** DO NOTHING **/) {
                if(_children[i]->Add(*_iter)) {
                    _elements.erase(_iter++);
                } else {
                    ++_iter;
                }
            }
        }

    } catch(...) {
        for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
            if(_children[i]) {
                delete _children[i];
                _children[i] = nullptr;
            }
        }
    }
}

template<typename T>
void Grid<T>::UnSubDivide() {

    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        Grid<T>* curNode = _children[i];
        Grid<T>* curNodeParent = curNode->_parent;
        for(std::vector<T>::iterator _iter = curNode->_elements.begin(); _iter != curNode->_elements.end(); ++_iter) {
            curNodeParent->_elements.push_back(*_iter);
        }
        delete _children[i];
        _children[i] = nullptr;
    }
}

template<typename T>
bool Grid<T>::Add(const T& elem) {

    if(ptr(elem)) {
        bool intersects_result = _bounds.Intersects(*ptr(elem));
        if(intersects_result == false) {
            return false;
        }
    }

    if(IsLeaf(this) == false) {
        bool result = false;
        for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
            result |= _children[i]->Add(elem);
        }
        return result;
    }
    _elements.push_back(elem);
    if(_elements.size() > MAX_ELEMENTS) {
        SubDivide();
    }
    return true;
}

template<typename T>
bool Grid<T>::Add(const T* elem) {
    return Add(*elem);
}

template<typename T>
bool Grid<T>::Remove(const T& elem) {

    if(ptr(elem) && _bounds.Intersects(*ptr(elem)) == false) return false;

    if(IsLeaf(this)) {
        return RemoveElement(elem);
    }

    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        _children[i]->Remove(elem);
    }

    bool all_children_are_leaves = true;
    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        if(IsLeaf(_children[i])) continue;
        all_children_are_leaves = false;
        break;
    }

    if(all_children_are_leaves) {
        unsigned long elements_in_children = 0;
        for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
            elements_in_children += _children[i]->NumberOfElementsInTree();
        }
        if(elements_in_children < MAX_ELEMENTS) {
            UnSubDivide();
        }
    }
    return true;
}

template<typename T>
bool Grid<T>::Remove(const T* elem) {
    return Remove(*elem);
}

template<typename T>
bool Grid<T>::Update(const T& elem) {
    if(Remove(elem)) {
        if(Add(elem)) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool Grid<T>::Update(const T* elem) {
    return Update(*elem);
}

template<typename T>
void Grid<T>::Update(std::vector<T>& elem) {
    std::vector<T>::iterator b = elem.begin();
    std::vector<T>::iterator e = elem.end();
    for(std::vector<T>::iterator _iter = b; _iter != e; ++_iter) {
        Update(*_iter);
    }
}


template<typename T>
bool Grid<T>::RemoveElement(const T& elem) {

    std::vector<T>::iterator b = _elements.begin();
    std::vector<T>::iterator e = _elements.end();
    std::vector<T>::iterator _iter = b;
    _iter = std::find(b, e, elem);
    if(_iter != _elements.end()) {
        _elements.erase(_iter);
        return true;
    }
    return false;
}

template<typename T>
void Grid<T>::Clear() {
    Clear(this);
}

template<typename T>
void Grid<T>::Clear(Grid<T>* node) {

    if(IsLeaf(node)) {
        node->_elements.clear();
        return;
    }
    
    for(std::size_t i = 0; i < MAX_CHILDREN; ++i) {
        node->_children[i]->Clear();
    }
    node->UnSubDivide();
    node->_elements.clear();

}

A2DE_END

#endif