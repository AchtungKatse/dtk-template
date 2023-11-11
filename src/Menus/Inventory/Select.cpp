#include "Menus/Inventory/Inventory.h"
#include "Input/Input.h"
#include "SFX/SFX.h"

// uVar2 = FUN_80253ff4(*(int *)(DAT_8056cb78 + 0xf8) -
//                          ((uint)(*(uint *)(DAT_8056cb78 + 0xfc) <
//                                  G_Inventory->field336_0x1b4) +
//                           G_Inventory->field335_0x1b0),
//                      *(uint *)(DAT_8056cb78 + 0xfc) - G_Inventory->field336_0x1b4, 0,
//                      DAT_800000f8 / 4000);

extern int FUN_80253ff4(int unk_1, int unk_2, int unk_3, int unk_4);
extern int *DAT_8056cb78;
extern int DAT_800000f8;

extern void format(char *output, char *format, int value);

extern void DrawCursor(int unk_1, int unk_2, int unk_3, int* unk4, int unk_5);
extern int* FUN_801866a4;

namespace Menus::Inventory
{

  int SelectEntry()
  {
    InventorySideMenu currentMenu;
    int menuIndexCpy;
    ControllerInput dpadNewInput;
    int selecting;
    ControllerInput input;
    ControllerInput dpadInput;
    ControllerInput dpadHeldInput;
    bool isValid;
    int oldMenuIndex;
    double dVar1;
    undefined8 uVar2;
    char menu_help_name[64];
    float l_cursorXPos;
    float l_cursorMoveSpeed;
    float l_cursorYoffset;
    Inventory *l_inventory;

    currentMenu = G_Inventory->currentOpenSideMenu;
    if (currentMenu == Cards)
    {
      if ((G_InventoryManager->menus[(char)G_Inventory->unk_index_array[0]].state & Enabled) == Hidden)
      {
        if (G_Inventory->forceExit != false)
        {
          G_InventoryManager->exitedMenuIndex = 5;
          return -3;
        }
        G_Inventory->currentOpenSideMenu = None;
      }
    }
    else if ((int)currentMenu < 0x1e)
    {
      if (currentMenu == KeyItems)
      {
        if ((G_InventoryManager->menus[(char)G_Inventory->unk_index_array[0]].state & Enabled) ==
            Hidden)
        {
          if (G_Inventory->field326_0x1a4 != 0)
          {
            G_InventoryManager->exitedMenuIndex = 3;
            G_InventoryManager->field35_0x2c = G_Inventory->field326_0x1a4;
            return -2;
          }
          if (G_Inventory->forceExit != false)
          {
            G_InventoryManager->exitedMenuIndex = 3;
            return -3;
          }
          G_Inventory->currentOpenSideMenu = None;
        }
      }
      else if ((int)currentMenu < 10)
      {
        if (currentMenu == None)
        {
          oldMenuIndex = G_Inventory->menuIndex;
          dpadNewInput = Input::GetKeyPressed(0);
          /* if not pressing left or (???) */

          if (((dpadInput.left >> 8 & 1) == 0) ||
              (selecting = Input::PressedBtn2(), selecting == 0))
          {
            input = Input::GetKeyPressed(0);
            // ! This might just blatantly be wrong
            if ((input.field4_0x1 & 0x10) == 0)
            {
              input = Input::GetKeyPressed(0);
              // ! Probably also wrong
              dpadHeldInput.field4_0x1 = input.field4_0x1 >> 9 & 1;
            }
            else
            {
              /* Default Cursor movement down */
              dpadHeldInput.down = 1;
            }
            if (dpadHeldInput.field4_0x1 == 0)
            {
              dpadInput = (ControllerInput)Input::Query(0);
              /* Is Left */
              if ((dpadInput.left >> 3 & 1) == 0)
              {
                dpadHeldInput = Input::Query(0);
                /* is right */
                if ((dpadHeldInput.right >> 2 & 1) == 0)
                {
                  dpadHeldInput = Input::Query(0);
                  /* is up */
                  if ((dpadHeldInput.up >> 1 & 1) == 0)
                  {
                    dpadHeldInput = Input::Query(0);
                    /* is down */
                    if ((dpadHeldInput.down & 1) != 0)
                    {
                      do
                      {
                        /* Move Down */
                        G_Inventory->menuIndex =
                            (uint)InventoryCursorMovements[G_Inventory->menuIndex].down;
                        isValid = (*InventoryCursorMovements[G_Inventory->menuIndex].Validate)();
                      } while (!isValid);
                    }
                  }
                  else
                  {
                    do
                    {
                      /* Move up */
                      G_Inventory->menuIndex =
                          (uint)InventoryCursorMovements[G_Inventory->menuIndex].up;
                      isValid = (*InventoryCursorMovements[G_Inventory->menuIndex].Validate)();
                    } while (!isValid);
                  }
                }
                else
                {
                  do
                  {
                    /* Move Right */
                    G_Inventory->menuIndex =
                        (uint)InventoryCursorMovements[G_Inventory->menuIndex].right;
                    isValid = (*InventoryCursorMovements[G_Inventory->menuIndex].Validate)();
                  } while (!isValid);
                }
              }
              else
              {
                do
                {
                  /* Move  cursor left */
                  G_Inventory->menuIndex = (uint)InventoryCursorMovements[G_Inventory->menuIndex].left;
                  isValid = (*InventoryCursorMovements[G_Inventory->menuIndex].Validate)();
                } while (!isValid);
              }
            }
            else
            {
              uVar2 = FUN_80253ff4(*(int *)(DAT_8056cb78 + 0xf8) -
                                       ((uint)(*(uint *)(DAT_8056cb78 + 0xfc) <
                                               G_Inventory->field336_0x1b4) +
                                        G_Inventory->field335_0x1b0),
                                   *(uint *)(DAT_8056cb78 + 0xfc) - G_Inventory->field336_0x1b4, 0,
                                   DAT_800000f8 / 4000);
              if (0x80000000 <
                  (uint)(500 < (uint)uVar2) + ((uint)(uVar2 >> 0x20) ^ 0x80000000))
              {
                SFX::PlaySound("SFX_SYS_MENU_CANCEL1");
                return -1;
              }
            }
          }
          else
          {
            if ((G_InventoryManager->menus[G_Inventory->menuIndices[oldMenuIndex + 1]].state & 4) !=
                Hidden)
              goto LAB_80186638;
            /* Selecting menus */
            switch (oldMenuIndex)
            {
            case 0:
              OpenDropdown(Characters, 1);
              return 1;
            case 1:
              OpenDropdown(Pixels, 1);
              return 1;
            case 2:
              OpenDropdown(Items, 1);
              return 1;
            case 3:
              SFX::PlaySound("SFX_SYS_MENU_DESIDE1");
              OpenKeyItems();
              G_Inventory->currentOpenSideMenu = KeyItemsSide;
              break;
            case 4:
              SFX::PlaySound("SFX_SYS_MENU_DESIDE1");
              OpenChapters();
              G_Inventory->currentOpenSideMenu = ChaptersSide;
              break;
            case 5:
              SFX::PlaySound("SFX_SYS_MENU_DESIDE1");
              OpenCards();
              G_Inventory->currentOpenSideMenu = CardsSide;
              break;
            case 6:
              SFX::PlaySound("SFX_SYS_MENU_DESIDE1");
              OpenRecipes();
              G_Inventory->currentOpenSideMenu = RecipesSide;
              break;
            case 7:
              SFX::PlaySound("SFX_SYS_MENU_DESIDE1");
              OpenMaps();
              G_Inventory->currentOpenSideMenu = MapsSide;
            }
          }
          /* Check if selected menu changed
             This changes the jiggling box, plays the sound, and changes the text */
          if (oldMenuIndex != G_Inventory->menuIndex)
          {
            SFX::PlaySound("SFX_SYS_MENU_CURSOR_MOVE1");
            if (G_Inventory->currentOpenSideMenu == None)
            {
              format(menu_help_name, "menu_help_%03d", G_Inventory->menuIndex);
              SetHelpText(G_InventoryManager->menus + G_Inventory->menuIndices[10], 0, menu_help_name);
            }
            /* Remove highlited to old menu index */
            G_InventoryManager->menus[G_Inventory->menuIndices[oldMenuIndex + 1]].state &= ~Highligted;
            /* Remove Jiggle from old box */
            G_InventoryManager->menus[G_Inventory->menuIndices[oldMenuIndex + 1]].state &= ~Jiggling;
            /* Highlight selected box */
            G_InventoryManager->menus[G_Inventory->menuIndices[G_Inventory->menuIndex + 1]].state |= Highligted;
            /* Add jiggle to new box */
            G_InventoryManager->menus[G_Inventory->menuIndices[G_Inventory->menuIndex + 1]].state |= Jiggling;

            G_Inventory->menuIndexCopy = oldMenuIndex;
            G_Inventory->field321_0x190 = 0;
            l_inventory = G_Inventory;
            G_Inventory->somethingMenuOld[0] = G_Inventory->somethingMenuCurrent[0];
            l_inventory->somethingMenuOld[1] = l_inventory->somethingMenuCurrent[1];
            l_inventory->somethingMenuOld[2] = l_inventory->somethingMenuCurrent[2];
            l_inventory->somethingMenuOld[3] = l_inventory->somethingMenuCurrent[3];
            l_inventory = G_Inventory;
            G_Inventory->unk_menuOld2[0] = G_Inventory->unk_menuCurrent2[0];
            l_inventory->unk_menuOld2[1] = l_inventory->unk_menuCurrent2[1];
            l_inventory->unk_menuOld2[2] = l_inventory->unk_menuCurrent2[2];
            l_inventory->unk_menuOld2[3] = l_inventory->unk_menuCurrent2[3];
          }

          l_cursorYoffset = 30;
          float cursorXoffset = 25;
          if (G_Inventory->currentOpenSideMenu == None)
          {
            menuIndexCpy = G_Inventory->menuIndex;
            if ((int)menuIndexCpy < 3)
            {
              (G_Inventory->targetCursorPos).x =
                  G_InventoryBoxEntries[menuIndexCpy].Position.x - cursorXoffset;
              (G_Inventory->targetCursorPos).y =
                  G_InventoryBoxEntries[G_Inventory->menuIndex].Position.y - l_cursorYoffset;
            }
            else
            {
              (G_Inventory->targetCursorPos).x =
                  *(float *)&G_InventoryManager->menus
                       [G_Inventory->menuIndices[menuIndexCpy + Pixels]]
                           .field27_0x24 -
                  cursorXoffset;
              (G_Inventory->targetCursorPos).y =
                  *(float *)&G_InventoryManager->menus
                       [G_Inventory->menuIndices[G_Inventory->menuIndex + 1]]
                           .field31_0x28 -
                  l_cursorYoffset;
            }
          }
        }
      }
      else if ((currentMenu == Chapters) &&
               ((G_InventoryManager->menus[(char)G_Inventory->unk_index_array[9]].state & Enabled) ==
                Hidden))
      {
        if (G_Inventory->forceExit != false)
        {
          G_InventoryManager->exitedMenuIndex = 4;
          return -3;
        }
        G_Inventory->currentOpenSideMenu = None;
      }
    }
    else if (currentMenu == Maps)
    {
      if ((G_InventoryManager->menus[(char)G_Inventory->unk_index_array[0]].state & Enabled) == Hidden)
      {
        if (G_Inventory->forceExit != false)
        {
          G_InventoryManager->exitedMenuIndex = 7;
          return -3;
        }
        G_Inventory->currentOpenSideMenu = None;
      }
    }
    else if ((((int)currentMenu < 0x32) && (currentMenu == Recipes)) &&
             ((G_InventoryManager->menus[(char)G_Inventory->unk_index_array[0]].state & Enabled) ==
              Hidden))
    {
      if (G_Inventory->forceExit != false)
      {
        G_InventoryManager->exitedMenuIndex = 6;
        return -3;
      }
      G_Inventory->currentOpenSideMenu = None;
    }
  LAB_80186638:
    /* Lerp cursor towards target */
    float G_CursorMoveSpeed = .25f;
    l_cursorMoveSpeed = G_CursorMoveSpeed;
    l_cursorXPos = (G_Inventory->cursorPosition).x;
    dVar1 = (double)599;
    (G_Inventory->cursorPosition).x =
        ((G_Inventory->targetCursorPos).x - l_cursorXPos) * G_CursorMoveSpeed + l_cursorXPos;
    l_cursorYoffset = (G_Inventory->cursorPosition).y;
    (G_Inventory->cursorPosition).y =
        ((G_Inventory->targetCursorPos).y - l_cursorYoffset) * l_cursorMoveSpeed + l_cursorYoffset;
    DrawCursor(dVar1, 0xb, 4, FUN_801866a4, 0);
    return 0;
  }
}
