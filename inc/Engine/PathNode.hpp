#ifndef PATHNODE_HPP
#define PATHNODE_HPP

#include <cmath>

#include "MapComponent.hpp"

class PathNode {
public:
	PathNode(const PathNode&);

	PathNode(const MapComponent* pos, PathNode* last, const MapComponent* to);

	/// set field before this one
	/**
	 * used when a new, shorter way to this node is found.
	 * automatically updates estimated cost
	 */
	void setLast(PathNode* last);

	inline PathNode* getLast() {
		return l;
	}

	inline const MapComponent* getField() const {
		return _mymc;
	}

	inline float getCost() const {
		return ec;
	}

private:
	/** \brief field
	 */
	const MapComponent* _mymc;

	/// node before this one
	/**
	 * pointer to the node that is one
	 * step before this one on the shortest
	 * possible way currently known
	 */
	PathNode* l;

	/** \brief known costs to this node
	 */
	float kc;

	/** \brief estimated total cost
	 */
	float ec;
};

#endif // PATHNODE_HPP
