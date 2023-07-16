#include "Group.hpp"

#include <algorithm>
#include <iostream>

namespace ConfigurationManager {

bool Group::operator==(const Group& rhs) const {
  return m_name == rhs.m_name;
}
bool Group::operator==(const std::string& rhsName) const {
  return m_name == rhsName;
}

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

 auto Group::getSubgroup(std::string name) const -> std::shared_ptr<Group> {
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

  auto Group::appendProperty(std::unique_ptr<IConfigurableProperty>&& property)
     -> bool {
   //check if already exists (use unordered_set)
   auto name = property->getName();
   auto foundProperty =
   std::find_if(m_properties.begin(), m_properties.end(),
                    [name](const std::unique_ptr<IConfigurableProperty>& p) {
                      return p->getName() == name;
                    });
   if (foundProperty != m_properties.end()) {
     return false;
   }

   m_properties.push_back(
       std::unique_ptr<IConfigurableProperty>(std::move(property)));
   return true;
  }

  auto Group::appendSubgroup(std::unique_ptr<Group>&& group)
      -> bool {
   // check if already exists (use unordered_set)
   auto name = group->getName();
   auto foundGroup =
       std::find_if(m_subgroups.begin(), m_subgroups.end(),
                    [name](const std::shared_ptr<Group>& p) {
                      return p->getName() == name;
                    });
   if (foundGroup != m_subgroups.end()) {
     return false;
   }

   m_subgroups.push_back(
       std::unique_ptr<Group>(std::move(group)));
   return true;
  }

  auto Group::removeSubgroup(const std::string& name) -> bool {
   // check if already exists (use unordered_set)
   auto group = std::find_if(m_subgroups.begin(), m_subgroups.end(),
                             [name](const std::shared_ptr<Group>& p) {
                               return p->getName() == name;
                             });
   if (group == m_subgroups.end()) {
     return false;
   }
   m_subgroups.erase(group);
   return true;
  }
 }  // namespace ConfigurationManager
