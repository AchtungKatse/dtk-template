typedef struct UNK_Struct
{
    int* unk1;
    int* unk2;
    int* unk3;
} UNK_Struct;

extern void FUN_80063034(int* param1);

void FUN_800a4b40(UNK_Struct* unkStruct)
{
  FUN_80063034(unkStruct->unk3 + 0x24);
}