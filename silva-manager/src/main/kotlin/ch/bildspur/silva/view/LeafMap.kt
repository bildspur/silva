package ch.bildspur.silva.view

import ch.bildspur.silva.model.Leaf
import ch.bildspur.silva.util.ColorMode
import ch.bildspur.silva.util.draw
import processing.core.PGraphics
import processing.core.PVector

class LeafMap(val canvas : PGraphics, val leafs : MutableList<Leaf> = mutableListOf()) {

    private val backgroundColor = ColorMode.color(22)
    private val borderColor = ColorMode.color(255)

    fun render()
    {
        canvas.draw {
            // draw background
            it.background(backgroundColor)

            // draw center trunk

            // draw leafs

            // draw border
            canvas.noFill()
            canvas.strokeWeight(1f)
            canvas.stroke(borderColor)
            canvas.rect(0f, 0f, (it.width - 1).toFloat(), (it.height - 1).toFloat())
        }
    }

    fun mouseMove(position: PVector)
    {

    }

    fun mouseDown(position : PVector)
    {

    }

    fun mouseUp(position : PVector)
    {

    }
}