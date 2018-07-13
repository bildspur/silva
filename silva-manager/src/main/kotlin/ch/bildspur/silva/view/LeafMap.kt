package ch.bildspur.silva.view

import ch.bildspur.silva.Sketch
import ch.bildspur.silva.model.Leaf
import ch.bildspur.silva.util.ColorMode
import ch.bildspur.silva.util.circularIntersect
import ch.bildspur.silva.util.draw
import ch.bildspur.silva.util.stackMatrix
import processing.core.PConstants
import processing.core.PGraphics
import processing.core.PVector
import processing.event.MouseEvent

class LeafMap(val canvas : PGraphics, val leafs : MutableList<Leaf> = mutableListOf()) {

    private val backgroundColor = ColorMode.color(42,54,59)
    private val borderColor = ColorMode.color(255)

    private val centerTrunkColor = ColorMode.color(254,206,171)
    private val centerTrunkSize = 50f

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
            it.ellipse(0f,0f, centerTrunkSize, centerTrunkSize)

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
    }

    private fun drawLeaf(g : PGraphics, leaf : Leaf)
    {
        if(leaf.selected)
            g.fill(selectedLeafColor)
        else
            g.fill(leafColor)

        // draw leaf
        if(leaf.location.circularIntersect(mousePosition, leafSize / 2f))
            g.stroke(255)
            else
            g.stroke(leafBorderColor)
        g.ellipse(leaf.location.x, leaf.location.y, leafSize, leafSize)

        // draw text
        g.fill(255f)
        g.textAlign(PConstants.CENTER, PConstants.CENTER)
        g.textSize(leafTextSize)
        g.text(leaf.index, leaf.location.x, leaf.location.y)
    }

    private fun pickLeafes(position : PVector) : List<Leaf>
    {
        return leafs.filter { it.location.circularIntersect(position, leafSize / 2f) }
    }

    fun mousePressed(position : PVector)
    {
        // check if deselect
        val picked = pickLeafes(position)

        leafs.forEach { it.selected = false }

        // select
        if(picked.isNotEmpty())
            picked.last().selected = true
    }

    fun mouseMoved(position: PVector)
    {
        mousePosition = position
    }

    fun mouseReleased(position : PVector)
    {

    }
}