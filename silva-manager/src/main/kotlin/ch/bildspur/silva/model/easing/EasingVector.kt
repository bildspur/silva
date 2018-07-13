package ch.bildspur.silva.model.easing

import com.google.gson.annotations.Expose
import processing.core.PVector

class EasingVector(var easing: Float = 0.1f) : PVector(), EasingObject {
    @Expose
    var target: PVector = PVector()

    override fun update() {
        add(PVector.sub(target, this).mult(easing))
    }
}