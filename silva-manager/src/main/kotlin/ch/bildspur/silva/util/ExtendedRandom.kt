package ch.bildspur.silva.util

import java.util.*

class ExtendedRandom @JvmOverloads constructor(seed: Long = System.currentTimeMillis()) {
    private val r: Random = Random(seed)

    @JvmOverloads
    fun randomBoolean(value: Float = 0.5f): Boolean {
        return randomFloat() <= value
    }

    @JvmOverloads
    fun randomFloat(max: Float = 1f): Float {
        return randomFloat(0f, max)
    }

    fun randomFloat(min: Float, max: Float): Float {
        return min + r.nextFloat() * (max - min)
    }

    @JvmOverloads
    fun randomInt(max: Int = 1): Int {
        return randomInt(0, max)
    }

    fun randomInt(min: Int, max: Int): Int {
        return Math.round(randomFloat((min - 0.49999).toFloat(), (max + 0.49999).toFloat()))
    }
}