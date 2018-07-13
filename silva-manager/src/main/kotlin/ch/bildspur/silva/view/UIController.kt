package ch.bildspur.silva.view

import ch.bildspur.silva.Sketch
import controlP5.ControlP5
import processing.core.PConstants
import processing.core.PGraphics

class UIController(private val parent : Sketch) {

    private lateinit var cp5 : ControlP5
    private lateinit var canvas : PGraphics

    private lateinit var map : LeafMap

    private val padding = 20f
    private var h = padding + 140f

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
        val mapCanvas = parent.createGraphics(canvas.width - (2 * padding).toInt(), canvas.height - (h + padding).toInt())
        map = LeafMap(mapCanvas)
    }

    fun render()
    {
        // draw title
        canvas.fill(255)
        canvas.textSize(20f)
        canvas.textAlign(PConstants.LEFT, PConstants.CENTER)
        canvas.text(Sketch.NAME, padding, padding)

        // render controls
        map.render()
        canvas.image(map.canvas, padding, h)
        cp5.draw()
    }
}