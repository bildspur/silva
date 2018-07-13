package ch.bildspur.silva.model

import ch.bildspur.silva.event.Event
import ch.bildspur.silva.model.easing.EasingVector
import com.google.gson.annotations.Expose

class Leaf(@Expose val index : Int,
           @Expose var distance : Int = 0,
           @Expose val position : EasingVector = EasingVector()) {

    var selected = false

    val onSelected = Event<Leaf>()

    init {
        onSelected += {
            selected = true
        }
    }

    fun update()
    {
        position.update()
    }
}