package ch.bildspur.silva.view

import ch.bildspur.silva.Sketch
import ch.bildspur.silva.util.ColorMode
import ch.bildspur.silva.util.translate
import controlP5.ControlP5
import processing.core.PConstants
import processing.core.PGraphics
import processing.core.PVector
import kotlin.math.roundToInt

class UIController(private val sketch: Sketch) {

    private lateinit var cp5: ControlP5
    private lateinit var canvas: PGraphics

    lateinit var map: LeafMap

    private val padding = 20f
    private val vpadding = 10f
    private val hpadding = 10f
    private val controlHeight = 25
    private val controlWidth = 100

    private var h = padding + 30f

    private val mapPosition = PVector()

    var isInitialized = false

    fun setup(canvas: PGraphics) {
        this.canvas = canvas

        val font = Sketch.instance.createFont("Helvetica", 100f)

        cp5 = ControlP5(sketch)
        cp5.setGraphics(canvas, 0, 0)
        cp5.isAutoDraw = false

        // change the original colors
        cp5.setColorForeground(ColorMode.color(255,132,124))
        cp5.setColorBackground(ColorMode.color(42,54,59))
        cp5.setFont(font, 14)
        cp5.setColorActive(ColorMode.color(255,132,124))

        setupControls()
        isInitialized = true
    }

    private fun setupControls() {
        // setup cp5 controls

        // new, load, save
        cp5.addButton("New")
                .setPosition(padding, h)
                .setSize(controlWidth, controlHeight)
                .onClick {
                    sketch.createNewProject()
                    sketch.initAppConfig()
                }

        cp5.addButton("Load")
                .setPosition(padding + (hpadding + controlWidth), h)
                .setSize(controlWidth, controlHeight)
                .onClick {
                    sketch.loadAppConfig()
                    sketch.initAppConfig()
                }

        cp5.addButton("Save")
                .setPosition(padding + (2 * (hpadding + controlWidth)).roundToInt(), h)
                .setSize(controlWidth, controlHeight)
                .onClick {
                    sketch.saveAppConfig()
                }
        h += hpadding + controlHeight

        // setup map
        mapPosition.x = padding
        mapPosition.y = h
        val mapCanvas = sketch.createGraphics(canvas.width - (2 * padding).toInt(), canvas.height - (h + padding).toInt())
        map = LeafMap(mapCanvas, sketch.appConfig)
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