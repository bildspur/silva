package ch.bildspur.silva.model

import ch.bildspur.silva.model.easing.EasingVector
import processing.core.PGraphics

class Leaf(val index : Int, var distance : Int = 0) {
    val location = EasingVector()

    var selected = false

    fun update()
    {
        location.update()
    }
}