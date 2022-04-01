#pragma once

#include "Node.hpp"
#include <iostream>
#include <vector>

namespace UML {

enum ACCESS { PUBLIC, PRIVATE, PROTECTED };

class AccessType {
  ACCESS m_access;
  AccessType(ACCESS aAccess) : m_access(aAccess) {}

 public:
  ~AccessType() = default;
  ACCESS getType() const { return m_access; }
  std::string toString() const;
  static AccessType *getInstance(ACCESS aAccess);
  friend std::ostream &operator<<(std::ostream &os, const AccessType &obj);
};

namespace AccessTypeProvider {
extern AccessType *m_public;
extern AccessType *m_protected;
extern AccessType *m_private;
}

using InvolvedTypes = std::vector<std::string>;

/**
 * @brief Class Attribute is an interface. 'void accept(NodeVisitor*)' should be
 * implemented in child classes
 *
 */

class Attribute : public Node {
 protected:
  std::string m_type;
  std::string m_id;
  AccessType *m_accessType;

 public:
  ~Attribute() { delete (m_accessType); }
  std::string getId() const { return m_id; }
  std::string getType() const { return m_type; }
  virtual InvolvedTypes getInvolvedTypes() = 0;
  void setAccessType(AccessType *p_accessType) { m_accessType = p_accessType; }
  const AccessType &getAccessType() const { return *m_accessType; }
};
}  // namespace UML