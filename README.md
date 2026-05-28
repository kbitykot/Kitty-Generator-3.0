# Kitty Generator 3.0

Kitty Generator is an interactive program that allows you to create, customize, and manage up to 5 individual kitties! Once your felines are generated, you can interact with them through a dynamic console menu.

---

## 🐾 Kitty Customization Attributes

When creating a kitty, you can fully configure the following traits:

* **Name:** Each kitty must have a unique name (case-insensitive enforcement).
* **Gender:** Choose between Male or Female.
* **Age & Life Stage:** 
  * Select a life stage: **Kitten** or **Adult**.
  * Assign an age number up to **10,000** (units represent months for kittens or years for adults). Kittens and adults can share the same age value while retaining their distinct life-stage status.
* **Fur Details:**
  * **Fur Length:** Choose from *Hairless, Short haired, Average fur, Long haired,* or *Extra fluffy*.
  * **Fur Color(s):** Input up to 3 distinct colors.
  * **Fur Pattern:** Choose up to 3 patterns (*Spots, Stripes, Patches, Speckles, or Point*). Alternatively, select *Plain* (must stand alone; cannot be combined with other patterns).
* **Eye Color(s):** Select up to 2 colors (supports heterochromia options).
* **Tail Length:** Choose from *Short, Medium,* or *Long*.
* **Kitty Size:** Dynamically scales based on your chosen life stage:
  * *Kitten Options:* Tiny, Small, Average size, Big
  * *Adult Options:* Small, Average size, Big, Monster
* **Personality:** Input up to 5 user-specified descriptive adjectives.
* **Accessory:** Equip your kitty with one of 5 distinct accessories:
  * *Ribbon* (Placement options: Head or Tail)
  * *Clothes* (Includes custom text description)
  * *Crown/Tiara*
  * *Socks or Boots*
  * *Hat* (Includes custom text description of the hat type)

---

## 🎮 Program Menu & Functionality

Once your first kitty is configured, the system provides a dynamic interaction menu with the following operations:

1. **Create another kitty** (Up to the 5-kitty limit)
2. **Interact with a kitty**
3. **View kitties**
4. **Save kitties**
5. **Exit program**

### 💾 Persistent Storage Management
The program features automated initialization checks. When you save your data and exit, your configurations are securely preserved. Upon relaunching the program, the system will automatically detect your existing data and ask if you would like to **create a new set of kitties** or **load your saved session**.

---

## ⚙️ Instructions & Usage

To run the program, execute the compiled binary and follow the step-by-step directions displayed directly in the console output. 

* **Output:** The program will print a complete breakdown of your kitties' customized attributes directly to the screen upon successful creation.
* **Data Serialization:** All kitty objects are automatically serialized and saved into a local `.dat` file, ensuring your data is securely stored for future interaction.
