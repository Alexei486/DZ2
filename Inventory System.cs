
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using System.Linq;

[System.Serializable]
public class InventorySystem
{
   [SerializeField] private List<InventorySlot> InventorySlots;



   public List<InventorySlot> InventorySlots => InventorySlots;
   public int inventorySize => InventorySlots.Count;

   public InventorySystem(int size)
    {
      InventorySlots = new List<InventorySlot>(size);

      for (int i = 0; i < size; i++)
      {
         InventorySlots.Add(new inventorySlot());
      }
      
      
    }
efef 


}
