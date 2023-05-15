#include "core/Attribute.hpp"

namespace UML {

AccessType *AccessTypeProvider::m_public = nullptr;
AccessType *AccessTypeProvider::m_protected = nullptr;
AccessType *AccessTypeProvider::m_private = nullptr;

std::string AccessType::toString() const {
  switch (m_access) {
    case ACCESS::PUBLIC:
      return "PUBLIC";
    case ACCESS::PRIVATE:
      return "PRIVATE";
    case ACCESS::PROTECTED:
      return "PROTECTED";
    default:
      std::cout << "int value of enum: " << m_access << std::endl;
      return "ACCESSTYPE_INVALID";
  }
}

std::ostream &operator<<(std::ostream &os, const AccessType &obj) {
  os << obj.toString();
  return os;
}

AccessType *AccessType::getInstance(ACCESS aAccess) {
  switch (aAccess) {
    case ACCESS::PUBLIC:
      if (AccessTypeProvider::m_public == nullptr)
        AccessTypeProvider::m_public = new AccessType(aAccess);
      return AccessTypeProvider::m_public;

    case ACCESS::PROTECTED:
      if (AccessTypeProvider::m_protected == nullptr)
        AccessTypeProvider::m_protected = new AccessType(aAccess);
      return AccessTypeProvider::m_protected;

    case ACCESS::PRIVATE:
      if (AccessTypeProvider::m_private == nullptr)
        AccessTypeProvider::m_private = new AccessType(aAccess);
      return AccessTypeProvider::m_private;

    default:
      return nullptr;
  }
}
}