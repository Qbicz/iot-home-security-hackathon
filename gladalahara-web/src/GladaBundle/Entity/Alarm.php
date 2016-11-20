<?php

namespace GladaBundle\Entity;

use Doctrine\ORM\Mapping as ORM;

/**
 * Alarm
 *
 * @ORM\Table(name="alarm")
 * @ORM\Entity(repositoryClass="GladaBundle\Repository\AlarmRepository")
 */
class Alarm
{
    /**
     * @var int
     *
     * @ORM\Column(name="id", type="integer")
     * @ORM\Id
     * @ORM\GeneratedValue(strategy="AUTO")
     */
    private $id;

    /**
     * @var \DateTime
     *
     * @ORM\Column(name="time", type="datetime")
     */
    private $time;

    /**
     * @var bool
     *
     * @ORM\Column(name="seen", type="boolean")
     */
    private $seen;
    /**
    * @ORM\ManyToOne(targetEntity="Sensor", inversedBy="alarms")
    * @ORM\JoinColumn(name="sensor_id", referencedColumnName="id")
    */
   private $sensor;

    /**
     * Get id
     *
     * @return int
     */
    public function getId()
    {
        return $this->id;
    }

    /**
     * Set time
     *
     * @param \DateTime $time
     *
     * @return Alarm
     */
    public function setTime($time)
    {
        $this->time = $time;

        return $this;
    }

    /**
     * Get time
     *
     * @return \DateTime
     */
    public function getTime()
    {
        return $this->time;
    }

    /**
     * Set seen
     *
     * @param boolean $seen
     *
     * @return Alarm
     */
    public function setSeen($seen)
    {
        $this->seen = $seen;

        return $this;
    }

    /**
     * Get seen
     *
     * @return bool
     */
    public function getSeen()
    {
        return $this->seen;
    }

    /**
     * Set sensor
     *
     * @param \GladaBundle\Entity\Sensor $sensor
     *
     * @return Alarm
     */
    public function setSensor(\GladaBundle\Entity\Sensor $sensor = null)
    {
        $this->sensor = $sensor;

        return $this;
    }

    /**
     * Get sensor
     *
     * @return \GladaBundle\Entity\Sensor
     */
    public function getSensor()
    {
        return $this->sensor;
    }
}
