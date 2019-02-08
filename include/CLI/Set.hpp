#pragma once

// Distributed under the 3-Clause BSD License.  See accompanying
// file LICENSE or https://github.com/CLIUtils/CLI11 for details.

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

// CLI Library includes
#include "CLI/StringTools.hpp"

namespace CLI {

class Set {
  protected:
    using storage_type = std::vector<std::string>;
    std::shared_ptr<storage_type> items_{std::make_shared<storage_type>()};
    std::shared_ptr<bool> ignore_case_{std::make_shared<bool>(false)};
    std::shared_ptr<bool> ignore_underscore_{std::make_shared<bool>(false)};

  public:
    using iterator = storage_type::iterator;
    using const_iterator = storage_type::iterator;

    Set(std::initializer_list<std::string> values) : items_(std::make_shared<storage_type>(values)) {}

    /// Ignore case when matching
    Set *ignore_case(bool value = true) {
        *ignore_case_ = value;
        return this;
    }

    /// Ignore underscores when matching
    Set *ignore_underscore(bool value = true) {
        *ignore_underscore_ = value;
        return this;
    }

    /// Get the status of ignore case
    bool get_ignore_case() const { return *ignore_case_; }

    /// Get the status of ignore underscore
    bool get_ignore_underscore() const { return *ignore_underscore_; }

    /// Get the underlying vector (provisional)
    const storage_type &get_items() const { return *items_; }

    /// Find a value in the set, taking into account ignore settings
    const_iterator find(const std::string &item) const {
        bool ignore_case = *ignore_case_;
        bool ignore_underscore = *ignore_underscore_;

        return std::find_if(
            items_->begin(), items_->end(), [ignore_case, ignore_underscore, &item](std::string item_in_set) {
                std::string item_local = item;

                if(ignore_case) {
                    item_local = detail::to_lower(item_local);
                    item_in_set = detail::to_lower(item_in_set);
                }

                if(ignore_underscore) {
                    item_local = detail::remove_underscore(item_local);
                    item_in_set = detail::remove_underscore(item_in_set);
                }

                return item_local == item_in_set;
            });
    }

    /// Check to see if an item is in the set
    bool contains(const std::string &item) const { return find(item) != items_->end(); }

    /// Insert an item at the end of the set
    bool insert(const std::string &item) {
        if(contains(item)) {
            return false;
        } else {
            items_->emplace_back(item);
            return true;
        }
    }

    /// Remove an item by name from the set. Returns true if the item was originally in the set.
    ///
    /// Note that this is not fast, but CLI11 sets should be mostly small and static
    bool discard(const std::string &item) {
        auto result = std::find(items_->begin(), items_->end(), item);
        if(result != items_->end()) {
            items_->erase(result);
            return true;
        } else {
            return false;
        }
    }

    /// Remove an item by name from the set, throw an error if the item is not present.
    void remove(const std::string &item);

    /// Get an item by number from the set
    const std::string &at(size_t n) const { return items_->at(n); }

    /// Get an item by number from the set (non-const)
    std::string &at(size_t n) { return items_->at(n); }

    /// Get an item by number from the set
    const std::string &operator[](size_t n) const { return (*items_)[n]; }

    /// Get an item by number from the set (non-const)
    std::string &operator[](size_t n) { return (*items_)[n]; }
};

} // namespace CLI
