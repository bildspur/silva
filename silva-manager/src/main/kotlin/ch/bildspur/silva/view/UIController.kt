package ch.bildspur.silva.view

import ch.bildspur.silva.Sketch
import ch.bildspur.silva.util.translate
import controlP5.ControlP5
import processing.core.PConstants
import processing.core.PGraphics
import processing.core.PVector

class UIController(private val parent: Sketch) {

    private lateinit var cp5: ControlP5
    private lateinit var canvas: PGraphics

    lateinit var map: LeafMap

    private val padding = 20f
    private var h = padding + 140f

    private val mapPosition = PVector()

    fun setup(canvas: PGraphics) {
        this.canvas = canvas

        cp5 = ControlP5(parent)
        cp5.setGraphics(canvas, 0, 0)
        cp5.isAutoDraw = false

        setupControls()
    }

    private fun setupControls() {
        // setup cp5 controls

        // setup map
        mapPosition.x = padding
        mapPosition.y = h
        val mapCanvas = parent.createGraphics(canvas.width - (2 * padding).toInt(), canvas.height - (h + padding).toInt())
        map = LeafMap(mapCanvas)
    }

    fun render() {
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

    fun mousePressed(position : PVector) {
        if(!inMapBounds(position))
            return

        map.mousePressed(mapToMap(position))
    }

    fun mouseDragged(position : PVector)
    {
        if(!inMapBounds(position))
            return

        map.mouseDragged(mapToMap(position))
    }

    fun mouseMoved(position : PVector) {
        if(!inMapBounds(position))
            return

        map.mouseMoved(mapToMap(position))
    }

    fun mouseReleased(position : PVector) {
        if(!inMapBounds(position))
            return

        map.mouseReleased(mapToMap(position))
    }

    private fun mapToMap(position : PVector) : PVector
    {
        return position.translate(PVector.mult(mapPosition,-1f)
                .translate(PVector.mult(PVector(map.canvas.width.toFloat(), map.canvas.height.toFloat()), -0.5f)))
    }

    private fun inMapBounds(position : PVector) : Boolean
    {
        return position.x >= mapPosition.x && position.x <= mapPosition.x + map.canvas.width
                && position.y >= mapPosition.y && position.y <= mapPosition.y + map.canvas.height
    }
}