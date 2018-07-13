package ch.bildspur.silva.view

import ch.bildspur.silva.Sketch
import ch.bildspur.silva.model.AppConfig
import ch.bildspur.silva.model.Leaf
import ch.bildspur.silva.util.ColorMode
import ch.bildspur.silva.util.circularIntersect
import ch.bildspur.silva.util.draw
import processing.core.PApplet
import processing.core.PConstants
import processing.core.PGraphics
import processing.core.PVector
import kotlin.math.roundToInt

class LeafMap(val canvas : PGraphics, val appConfig : AppConfig) {

    private val leafs = appConfig.leafs

    private val backgroundColor = ColorMode.color(42,54,59)
    private val borderColor = ColorMode.color(255)

    private val centerTrunkColor = ColorMode.color(254,206,171)
    private val centerTrunkSize = 50f
    private val centerTrunkPosition = PVector(0f, 0f)

    private val leafColor = ColorMode.color(255,132,124)
    private val selectedLeafColor = ColorMode.color(232,74,95)
    private val leafBorderColor = ColorMode.color(54,54,54)
    private val leafSize = 30f
    private val leafTextSize = 12f

    private val infoColor = ColorMode.color(153,184,152)
    private val infoTextSize = 14f

    private val font = Sketch.instance.createFont("Helvetica", 100f)

    private var mousePosition = PVector()

    fun render()
    {
        // render
        canvas.draw {
            // set font
            it.textFont(font)

            // draw background
            it.background(backgroundColor)

            it.pushMatrix()
            it.translate(it.width / 2f, it.height / 2f)

            // draw center trunk
            it.fill(centerTrunkColor)
            it.noStroke()
            it.ellipseMode(PConstants.CENTER)
            it.ellipse(centerTrunkPosition.x, centerTrunkPosition.y, centerTrunkSize, centerTrunkSize)

            // draw leafs
            // update leafes
            leafs.forEach { leaf ->
                leaf.update()
                drawLeaf(it, leaf)
            }

            it.popMatrix()

            // draw border
            canvas.noFill()
            canvas.strokeWeight(1f)
            canvas.stroke(borderColor)
            canvas.rect(0f, 0f, (it.width - 1).toFloat(), (it.height - 1).toFloat())
        }

        updateLeafDistances()
    }

    private fun drawLeaf(g : PGraphics, leaf : Leaf)
    {
        // show info
        if(leaf.selected)
        {
            g.noFill()
            g.stroke(infoColor)

            val radius = leaf.position.dist(centerTrunkPosition)
            val centerPoint = PVector.lerp(leaf.position, centerTrunkPosition, 0.5f)

            // draw circle
            g.ellipse(0f, 0f, radius * 2f, radius * 2f)

            // draw line
            g.line(centerTrunkPosition.x, centerTrunkPosition.y, leaf.position.x, leaf.position.y)

            // draw text
            g.fill(255f)
            g.textAlign(PConstants.CENTER, PConstants.CENTER)
            g.textSize(infoTextSize)
            g.text(leaf.distance, centerPoint.x, centerPoint.y)
        }

        if(leaf.selected)
            g.fill(selectedLeafColor)
        else
            g.fill(leafColor)

        // draw leaf
        if(leaf.position.circularIntersect(mousePosition, leafSize / 2f))
            g.stroke(255)
            else
            g.stroke(leafBorderColor)
        g.ellipse(leaf.position.x, leaf.position.y, leafSize, leafSize)

        // draw text
        g.fill(255f)
        g.textAlign(PConstants.CENTER, PConstants.CENTER)
        g.textSize(leafTextSize)
        g.text(leaf.index, leaf.position.x, leaf.position.y)
    }

    private fun pickLeafs(position : PVector) : List<Leaf>
    {
        return leafs.filter { it.position.circularIntersect(position, leafSize / 2f) }
    }

    private fun updateLeafDistances()
    {
        if(leafs.isEmpty())
            return

        val maxDistance = leafs.map { it.position.dist(centerTrunkPosition) }.max()!!

        leafs.forEach {
            val distance = it.position.dist(centerTrunkPosition)
            it.distance = PApplet.map(distance, 0f, maxDistance, 0f, 255f).roundToInt()
        }
    }

    fun mousePressed(position : PVector)
    {
        // check if deselect
        val picked = pickLeafs(position)

        leafs.forEach { it.selected = false }

        // select
        if(picked.isNotEmpty()) {
            val leaf = picked.last()
            leaf.onSelected.invoke(leaf)
        }
    }

    fun mouseMoved(position: PVector)
    {
        mousePosition = position
    }

    fun mouseDragged(position : PVector)
    {
        leafs.filter { it.selected }.forEach { it.position.target = position }
    }

    fun mouseReleased(position : PVector)
    {

    }
}