#pragma once

/**
 * Simple PseudoRandom number generator class.
 */
class CPseudoRandom
{
public:
    /**
     * Constructor
     * \param seed The seed for the random number generator 
     */
    CPseudoRandom(int seed=1235) { mInitialSeed = (unsigned int)seed; Reset(); }

    /** Copy constructor (deleted) */
    CPseudoRandom(const CPseudoRandom &) = delete;

    /** Assignment operator (deleted) */
    void operator=(const CPseudoRandom &) = delete;

    /**
     * Set a new seed for the generator
     * \param seed The seed for the random number generator 
     */
    void Seed(int seed) { mInitialSeed = (unsigned int)seed; Reset(); }

    /** Destructor */
    virtual ~CPseudoRandom() {}

    /** Reset the generator back to the initial seed */
    void Reset() { mSeed = mInitialSeed; }

    /**
     * Generator a random double value
     * \param fm Minimum value
     * \param to Maximum value
     * \return Random double value
     */
    double Random(double fm, double to) { return Rnd() / 2147483648.0 * (to - fm) + fm; }

    /**
     * Generator a random integer value
     * \param fm Minimum value
     * \param to Maximum value
     * \return Random integer value
     */
    int Random(int fm, int to) { return (int)Random((double)fm, (double)(to + 1)); }

private:
    /** Generator a random integer from 0 to 2^31-1 
     * \return Random integer */
    int Rnd() { return(mSeed = (1103515245 * mSeed + 12345) % mMod); }

    unsigned int mInitialSeed = 10;     ///< The initial seed value as set
    unsigned int mMod = 2147483648;     ///< 2^31
    unsigned int mSeed;                 ///< Current seed value

};

