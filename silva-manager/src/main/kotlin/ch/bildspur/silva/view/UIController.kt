package ch.bildspur.silva.view

import ch.bildspur.silva.Sketch
import controlP5.ControlP5
import processing.core.PConstants
import processing.core.PGraphics

class UIController(private val parent : Sketch) {

    lateinit var cp5 : ControlP5
    lateinit var canvas : PGraphics

    fun setup(canvas : PGraphics)
    {
        this.canvas = canvas

        cp5 = ControlP5(parent)
        cp5.setGraphics(canvas, 0, 0)
        cp5.isAutoDraw = false

        setupControls()
    }

    private fun setupControls()
    {

    }

    fun render()
    {
        // draw title
        canvas.fill(255)
        canvas.textSize(20f)
        canvas.textAlign(PConstants.LEFT, PConstants.CENTER)
        canvas.text(Sketch.NAME, 20f, 20f)

        // render controls
        cp5.draw()
    }
}