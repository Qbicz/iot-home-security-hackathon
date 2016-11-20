<?php

namespace GladaBundle\Entity;

use Doctrine\ORM\Mapping as ORM;

/**
 * Sensor
 *
 * @ORM\Table(name="sensor")
 * @ORM\Entity(repositoryClass="GladaBundle\Repository\SensorRepository")
 */
class Sensor
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
     * @var string
     *
     * @ORM\Column(name="name", type="string", length=255)
     */
    private $name;

    /**
     * @var int
     *
     * @ORM\Column(name="room", type="integer")
     */
    private $room;

    /**
     * @var int
     *
     * @ORM\Column(name="type", type="integer")
     */
    private $type;
    /**
     * @ORM\OneToMany(targetEntity="Result", mappedBy="sensor")
     */
    private $results;
    /**
     * @ORM\OneToMany(targetEntity="Alarm", mappedBy="sensor")
     */
    private $alarms;
    public function __construct()
    {
        $this->results = new ArrayCollection();
        $this->alarms = new ArrayCollection();
    }


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
     * Set name
     *
     * @param string $name
     *
     * @return Sensor
     */
    public function setName($name)
    {
        $this->name = $name;

        return $this;
    }

    /**
     * Get name
     *
     * @return string
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * Set room
     *
     * @param integer $room
     *
     * @return Sensor
     */
    public function setRoom($room)
    {
        $this->room = $room;

        return $this;
    }

    /**
     * Get room
     *
     * @return int
     */
    public function getRoom()
    {
        return $this->room;
    }

    /**
     * Set type
     *
     * @param integer $type
     *
     * @return Sensor
     */
    public function setType($type)
    {
        $this->type = $type;

        return $this;
    }

    /**
     * Get type
     *
     * @return int
     */
    public function getType()
    {
        return $this->type;
    }

    /**
     * Add result
     *
     * @param \GladaBundle\Entity\Result $result
     *
     * @return Sensor
     */
    public function addResult(\GladaBundle\Entity\Result $result)
    {
        $this->results[] = $result;

        return $this;
    }

    /**
     * Remove result
     *
     * @param \GladaBundle\Entity\Result $result
     */
    public function removeResult(\GladaBundle\Entity\Result $result)
    {
        $this->results->removeElement($result);
    }

    /**
     * Get results
     *
     * @return \Doctrine\Common\Collections\Collection
     */
    public function getResults()
    {
        return $this->results;
    }

    /**
     * Add alarm
     *
     * @param \GladaBundle\Entity\Alarm $alarm
     *
     * @return Sensor
     */
    public function addAlarm(\GladaBundle\Entity\Alarm $alarm)
    {
        $this->alarms[] = $alarm;

        return $this;
    }

    /**
     * Remove alarm
     *
     * @param \GladaBundle\Entity\Alarm $alarm
     */
    public function removeAlarm(\GladaBundle\Entity\Alarm $alarm)
    {
        $this->alarms->removeElement($alarm);
    }

    /**
     * Get alarms
     *
     * @return \Doctrine\Common\Collections\Collection
     */
    public function getAlarms()
    {
        return $this->alarms;
    }
}
