package ch.bildspur.silva

import ch.bildspur.silva.view.UIController
import processing.core.PApplet
import processing.core.PConstants
import processing.core.PImage


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

    val ui = UIController(this)

    override fun settings() {
        size(WINDOW_WIDTH, WINDOW_HEIGHT, PConstants.FX2D)
    }

    override fun setup() {
        surface.setTitle("$NAME - $VERSION")
        surface.setIcon(loadImage("images/silva-logo-128.png"))

        ui.setup(g)
    }

    override fun draw() {
        background(5)
        ui.render()
    }

    fun run()
    {
        this.runSketch()
    }
}