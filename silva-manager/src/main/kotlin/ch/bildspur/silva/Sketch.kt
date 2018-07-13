package ch.bildspur.silva

import processing.core.PApplet
import processing.core.PConstants


/**
 * Created by cansik on 04.02.17.
 */
class Sketch : PApplet() {
    companion object {
        @JvmStatic
        val WINDOW_WIDTH = 1280
        @JvmStatic
        val WINDOW_HEIGHT = 800

        @JvmStatic
        val NAME = "Silva Manager"

        @JvmStatic
        val URI_NAME = "silva"

        @JvmStatic
        val VERSION = "0.1"

        @JvmStatic
        fun map(value: Double, start1: Double, stop1: Double, start2: Double, stop2: Double): Double {
            return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1))
        }
    }

    init {
    }

    override fun settings() {
        size(WINDOW_WIDTH, WINDOW_HEIGHT, PConstants.FX2D)
    }

    override fun setup() {
    }

    override fun draw() {
        background(5)
    }

    fun run()
    {
        this.runSketch()
    }
}