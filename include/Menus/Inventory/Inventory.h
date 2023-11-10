#include "../Inventory/Types.h"
#include "../../Menus/Cursor/Cursor.h"
#include "../../Menus/MenuBoxEntry.h"

namespace Menus::Inventory
{
    int Select();
    void OpenDropdown(InventoryMenuIndex index, int source);
    void OpenKeyItems();
    void OpenChapters();
    void OpenCards();
    void OpenRecipes();
    void OpenMaps();
    void SetHelpText(InventoryMenuEntry* unk_1, int unk_2, char* text);

}

extern Menus::Inventory::Inventory* G_Inventory;
extern Menus::Inventory::InventoryManager* G_InventoryManager;
extern Menus::Cursor::CursorMovement InventoryCursorMovements[8];
extern Menus::MenuBoxEntry G_InventoryBoxEntries[11];
