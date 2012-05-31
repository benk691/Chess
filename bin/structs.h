struct Time
{
    unsigned char min;
    unsigned char sec;

    Time(unsigned char m = 0, unsigned char s = 0)
        : min(m), sec(s)
    {}
};
