package ch.bildspur.silva.network

import ch.bildspur.silva.Sketch
import oscP5.OscMessage
import kotlin.concurrent.thread

class TreeConnection(val sketch : Sketch,
                     val osc : OscController) {


    @Volatile var isRunning = false

    @Volatile private var recordMessages = false
    val messageBuffer = mutableListOf<OscMessage>()

    init {
        osc.onOscMessage += {
            if(recordMessages)
                messageBuffer.add(it)
        }
    }

    fun readDataFromTree() {

    }

    fun writeDataToTree() {
        isRunning = true
        thread {
            println("writing data to tree...")
            sketch.appConfig.leafs.forEachIndexed {i, leaf ->
                println("updating $i with distance ${leaf.distance}...")
                leaf.selected = true
                osc.sendMessage("/silva/update", i.toFloat(), leaf.distance.toFloat())
                Thread.sleep(500)
                leaf.selected = false
            }

            Thread.sleep(1000)
            saveTree()

            Thread.sleep(1000)
            println("done!")
            isRunning = false
        }
    }

    fun saveTree()
    {
        println("saving configuration...")
        osc.sendMessage("/silva/save", 0f)
    }
}