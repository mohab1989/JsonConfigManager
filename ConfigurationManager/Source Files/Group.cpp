#include "Group.hpp"

#include <algorithm>
#include <iostream>

namespace ConfigurationManager {

auto Group::getPropertyValue(std::string name) -> std::any {
  auto property =
      std::find_if(m_properties.begin(), m_properties.end(),
                   [name](const std::unique_ptr<IConfigurableProperty>& p) {
                     return p->getName() == name;
                   });
  if (property == m_properties.end()) {
    return std::any();
  }
  return (*property)->getValue();
}

 auto Group::getSubgroup(std::string name) -> std::shared_ptr<Group> {
   auto group = std::find_if(m_subgroups.begin(), m_subgroups.end(),
      [name](const std::shared_ptr<Group>& p) { return p->getName() == name; });
   if (group == m_subgroups.end()) {
     return nullptr;
   }
   return *group;
 }

 auto Group::setPropertyValue(std::string name, std::any value) -> bool {
   auto property =
       std::find_if(m_properties.begin(), m_properties.end(),
                    [name](const std::unique_ptr<IConfigurableProperty>& p) {
                      return p->getName() == name;
                    });
   if (property == m_properties.end()) {
     return false;
   }
   return (*property)->setValue(value);
 }
 }  // namespace ConfigurationManager
