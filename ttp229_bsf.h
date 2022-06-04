class TTP229_BSF
{
  private:
    bool keypad_flag;
    int __scl_pin;
    int __sdo_pin;
    uint32_t key_data;
    uint16_t key_pressed;
    void handleKeyPadInterrupt(void);
    static void onKeypadInterrupt(void);
  public:
    TTP229_BSF();
    void init(void);    
    void setPins(int scl_pin, int sdo_pin);
    void setInterruptMode(void);
    void ReadKeypad(void);          // call directly if not Interrupt mode & after this call getKey()
    bool getFlag(void);             // currently not used
    void clearFlag(void);           // currently not used
    uint16_t getKey(void);          // return 16 bit value of all key 
    uint16_t getPressedKey(void);   // return key number which is pressed
    void clearPressedKey(void);     // clear key number call after every read getPressedKey()
    ~TTP229_BSF();
};
extern TTP229_BSF ttp;
