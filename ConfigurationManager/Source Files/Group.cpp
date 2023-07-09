#include <algorithm>
#include <iostream>

#include "Group.hpp"

namespace ConfigurationManager {

auto Group::getPropertyValue(std::string name) -> std::any {
  auto property = std::find_if(
      m_properties.begin(), m_properties.end(),
      [name](IConfigurableProperty* p) { return p->getName() == name; });
  if (property == m_properties.end()) {
    return std::any();
  }
  return (*property)->getValue();
}

//auto Group::getSubgroup(std::string name) -> std::shared_ptr<Group> {
//  auto group = std::find_if(m_subgroups.begin(), m_subgroups.end(),
//                            [name](Group p) { return p.getName() == name; });
//  if (group == m_subgroups.end()) {
//    return nullptr;
//  }
//  return std::make_shared<Group>(group);
//}
}  // namespace ConfigurationManager
