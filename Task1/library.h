#pragma once

#include <array>
#include <iostream>
#include <map>
#include <set>
#include <string>

#define ZONEZ 1
#define RACKS 10
#define SECTIONS 7
#define SHELFS 4

#define LIMIT(min, value, max) (((value) >= (min)) && ((value) <= (max)))

enum class AddProduct { INCORRECT_INPUT_DATA, CELL_IS_OCCUPIED_BY_ANOTHER_PRODUCT, NOT_ENOUGH_SPACE_IN_THE_CELL, ADDED_EXISTED_PROSUCT_SUCCESS, ADDED_NEW_PROSUCT_SUCCESS };

enum class RemoveProduct { INCORRECT_INPUT_DATA, CELL_IS_OCCUPIED_BY_ANOTHER_PRODUCT, COMPLETE_REMOVAL_PRODUCT_SUCCESS, REMOVAL_PRODUCT_SUCCESS, NOT_FOUND_PRODUCT };
