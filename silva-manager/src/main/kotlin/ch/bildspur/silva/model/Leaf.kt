package ch.bildspur.silva.model

import ch.bildspur.silva.model.easing.EasingVector

class Leaf(val index : Int, var distance : Int = 0) {
    val position = EasingVector()

    var selected = false

    fun update()
    {
        position.update()
    }
}