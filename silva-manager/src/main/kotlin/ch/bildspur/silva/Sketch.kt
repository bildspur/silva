package ch.bildspur.silva

import ch.bildspur.silva.configuration.ConfigurationController
import ch.bildspur.silva.model.AppConfig
import ch.bildspur.silva.model.Leaf
import ch.bildspur.silva.model.TreeInformation
import ch.bildspur.silva.network.OscController
import ch.bildspur.silva.network.TreeConnection
import ch.bildspur.silva.util.ExtendedRandom
import ch.bildspur.silva.view.UIController
import processing.core.PApplet
import processing.core.PConstants
import processing.core.PVector


/**
 * Created by cansik on 04.02.17.
 */
class Sketch : PApplet() {
    companion object {
        @JvmStatic
        val WINDOW_WIDTH = 800
        @JvmStatic
        val WINDOW_HEIGHT = 1024

        @JvmStatic
        val NAME = "Silva Manager"

        @JvmStatic
        val URI_NAME = "silva"

        @JvmStatic
        val VERSION = "0.1"

        @JvmStatic
        lateinit var instance: Sketch

        @JvmStatic
        fun map(value: Double, start1: Double, stop1: Double, start2: Double, stop2: Double): Double {
            return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1))
        }
    }

    private val ui = UIController(this)

    private val config = ConfigurationController()

    val osc = OscController(this)

    val treeConnection = TreeConnection(this, osc)

    var appConfig = AppConfig()

    private val rnd = ExtendedRandom()

    override fun settings() {
        size(WINDOW_WIDTH, WINDOW_HEIGHT, PConstants.P2D)
        pixelDensity = 2

        instance = this
    }

    override fun setup() {
        surface.setTitle("$NAME - $VERSION")
        surface.setIcon(loadImage("images/silva-logo-128.png"))

        appConfig = config.loadAppConfig()
        initAppConfig()

        ui.setup(g)
        osc.setup(appConfig.oscInPort, appConfig.oscOutPort)
    }

    override fun draw() {
        background(5)
        ui.render()
    }

    override fun stop() {
        super.stop()
        osc.stop()
    }

    fun run()
    {
        this.runSketch()
    }

    override fun mouseDragged() {
        ui.mouseDragged(PVector(mouseX.toFloat(), mouseY.toFloat()))
    }

    override fun mousePressed() {
        ui.mousePressed(PVector(mouseX.toFloat(), mouseY.toFloat()))
    }

    override fun mouseMoved() {
        ui.mouseMoved(PVector(mouseX.toFloat(), mouseY.toFloat()))
    }

    override fun mouseReleased() {
        ui.mouseReleased(PVector(mouseX.toFloat(), mouseY.toFloat()))
    }

    fun loadAppConfig() {
        appConfig = config.loadAppConfig()
    }

    fun initAppConfig()
    {
        if(ui.isInitialized)
            ui.map.appConfig = appConfig

        // add listener
        appConfig.leafs.forEach {
            it.onSelected += {
                println("selecting ${it.index}...")
                osc.sendMessage("/silva/select", it.index.toFloat())
            }
        }
    }

    fun createNewProject() {
        appConfig = AppConfig()
        (0 until appConfig.defaultLeafCount).forEach {
            val leaf = Leaf(it)
            leaf.position.target = PVector.random2D().mult(rnd.randomFloat(50f, 300f))
            appConfig.leafs.add(leaf)
        }
    }

    fun saveAppConfig() {
        config.saveAppConfig(appConfig)
    }


}